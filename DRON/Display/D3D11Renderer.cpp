/**
 *  Engine/Display/D3D11Renderer.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include "D3D11Renderer.hpp"

#include <cassert>
#include <sstream>
#include <vector>
#include <D3DX11.h>
#include <D3Dcompiler.h>
#include <aiMesh.h>

#include "DisplaySettings.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/CameraComponent.hpp"
#include "../Entity/Components/RenderableComponent.hpp"
#include "../Resource/MeshLocator.hpp"
#include "../Resource/PixelShaderLocator.hpp"
#include "../Resource/VertexShaderLocator.hpp"
#include "../Utility/DXUtil.hpp"
#include "../Utility/Geometry.hpp"

template< typename T >
D3D11Renderer::BufferMapping< T >::BufferMapping( ID3D11Buffer* buffer,
	ID3D11DeviceContext* dc, D3D11_MAP map_flag )
: _buffer_ptr( buffer ), _dc_ptr( dc )
{
	_dc_ptr->Map( _buffer_ptr, 0, map_flag, 0, &_data );
}

template< typename T >
D3D11Renderer::BufferMapping< T >::~BufferMapping()
{
	_dc_ptr->Unmap( _buffer_ptr, 0 );
}

D3D11Renderer::D3D11Renderer( HWND window,
							  DisplaySettings& ds,
							  EntitySystem& es )
    : _device(), _swap_chain( _device, ds, window ),
	  _depth_stencil_buffer( 0 ), _render_target_view( 0 ),
	  _depth_stencil_view( 0 ), _instance_buffer( 0 ), _per_frame_buffer( 0 ),
	  _entity_system( es )
{
	XMStoreFloat4x4NC( &_world_mx, XMMatrixIdentity() );
	InitializeBuffers();
    OnResize( ds );
}

D3D11Renderer::~D3D11Renderer()
{
	DXRelease( _per_frame_buffer );
	DXRelease( _depth_stencil_buffer );
	DXRelease( _depth_stencil_view );
	DXRelease( _render_target_view );
}

void D3D11Renderer::OnResize( DisplaySettings& ds )
{
	// Release the old views, as they hold references to the buffers we
	// will be destroying.  Also release the old depth/stencil buffer.
	DXRelease( _render_target_view );
    DXRelease( _depth_stencil_view );
    DXRelease( _depth_stencil_buffer );

	// Resize the swap chain and recreate the render target view.
	_swap_chain.Resize( ds );

    ID3D11Texture2D* back_buffer = _swap_chain.GetBuffer();
    HR( _device.GetRawDevicePtr()->CreateRenderTargetView( back_buffer, 0, &_render_target_view ) );
    DXRelease( back_buffer );

	// Create the depth/stencil buffer and view.
	D3D11_TEXTURE2D_DESC dsd;
	
	dsd.Width     = ds._width;
	dsd.Height    = ds._height;
	dsd.MipLevels = 1;
	dsd.ArraySize = 1;
	dsd.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsd.SampleDesc.Count   = 1; // multisampling must match
	dsd.SampleDesc.Quality = 0; // swap chain values.
	dsd.Usage          = D3D11_USAGE_DEFAULT;
	dsd.BindFlags      = D3D11_BIND_DEPTH_STENCIL;
	dsd.CPUAccessFlags = 0; 
	dsd.MiscFlags      = 0;

    _device.GetRawDevicePtr()->CreateTexture2D(&dsd, 0, &_depth_stencil_buffer);
    _device.GetRawDevicePtr()->CreateDepthStencilView(_depth_stencil_buffer, 0, &_depth_stencil_view);

	// Bind the render target view and depth/stencil view to the pipeline.
	_device.GetRawContextPtr()->OMSetRenderTargets(1, &_render_target_view, _depth_stencil_view);

	// set the viewport
	_view_port.TopLeftX = 0;
	_view_port.TopLeftY = 0;
	_view_port.Width    = static_cast< float >( ds._width );
	_view_port.Height   = static_cast< float >( ds._height );
	_view_port.MinDepth = 0.0f;
	_view_port.MaxDepth = 1.0f;

	_device.GetRawContextPtr()->RSSetViewports(1, &_view_port);

    // the aspect ratio may have changed, so refigure the projection matrices
	XMStoreFloat4x4( &_perspec_mx,
		XMMatrixPerspectiveFovLH( 0.25f * XM_PI,
			static_cast< float >( ds._width ) / static_cast< float >( ds._height ),
			0.1f, 100.0f )
	);

	XMStoreFloat4x4( &_ortho_mx,
		XMMatrixOrthographicLH( static_cast< float >( ds._width ) / 16.0f,
			static_cast< float >( ds._height ) / 16.0f, 1.0f, 100.0f )
	);

	/*
    if( ds._fullscreen )
        _swap_chain_ptr->SetFullscreenState( true , 0 );
		*/
}

void D3D11Renderer::SetFullscreen( bool go_fs )
{
	/*
    BOOL is_fs;
    IDXGIOutput* dummy;
    _swap_chain_ptr->GetFullscreenState( &is_fs, &dummy );

    // damn ms typedefs >:(
    if( ( is_fs == TRUE && !go_fs ) ||
        ( is_fs == FALSE && go_fs ) )
        _swap_chain_ptr->SetFullscreenState( go_fs, 0 );
		*/
}

bool D3D11Renderer::InitializeBuffers()
{
    D3D11_BUFFER_DESC bd;
    bd.ByteWidth = sizeof( InstanceData ) * 100; //4 for pos, rot_quat, scale, color 
    bd.Usage = D3D11_USAGE_DYNAMIC;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bd.MiscFlags = 0;

	HR( _device.GetRawDevicePtr()->CreateBuffer( &bd, 0, &_instance_buffer ) );


    bd.ByteWidth = sizeof( XMMATRIX ) * 3;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

	HR( _device.GetRawDevicePtr()->CreateBuffer( &bd, 0, &_per_frame_buffer ) );

    return true;
}

void D3D11Renderer::Draw( std::vector< Entity >& entities, Entity camera )
{
	ClearViewsAndRenderTargets();

    // set defaults for the depth/stencil and blend states
    _device.GetRawContextPtr()->OMSetDepthStencilState( 0, 0 );

    float bf[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    _device.GetRawContextPtr()->OMSetBlendState( 0, bf, 0xffffffff );

	BaseComponent* cc = 0;
	_entity_system.GetComponent( camera, COMPONENT_CAMERA, &cc );
	assert( cc );
	CameraComponent::Data ccd = static_cast< CameraComponent* >( cc )->GetData();
	XMStoreFloat4x4NC( &_view_mx, XMMatrixLookAtLH( ccd._position, ccd._lookat, ccd._up ) );

	WVP per_frame;
	per_frame._world = XMMatrixTranspose( XMLoadFloat4x4( &_world_mx ) );
	per_frame._view  = XMMatrixTranspose( XMLoadFloat4x4( &_view_mx ) );
	per_frame._proj  = XMMatrixTranspose( XMLoadFloat4x4( &_perspec_mx ) );
	_device.GetRawContextPtr()->UpdateSubresource( _per_frame_buffer, 0, 0, &per_frame, 0, 0 );

	_device.GetRawContextPtr()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	Entity e = entities.front();
	cc = 0;
	_entity_system.GetComponent( e, COMPONENT_RENDERABLE, &cc );
	assert( cc );
	RenderableComponent::Data rcd = static_cast< RenderableComponent* >( cc )->GetData();

	MeshLocator ml( _device.GetRawDevicePtr() );
	MeshResource& m = ml.Request( rcd._mesh_name );
	Mesh& mesh = *m.Data();

	InstanceData id;
	id._translation = XMFLOAT3( 0.0f, 0.0f, 0.0f );
	id._rotation = XMFLOAT4( 0.0f, 0.0f, 0.0f, 1.0f );
	id._scale = XMFLOAT3( 1.0f, 1.0f, 1.0f );
	id._color = XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f );

	D3D11_MAPPED_SUBRESOURCE msr;
	_device.GetRawContextPtr()->Map( _instance_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr );
	InstanceData* id_ptr = static_cast< InstanceData* >( msr.pData );
	id_ptr[ 0 ] = id;
	_device.GetRawContextPtr()->Unmap( _instance_buffer, 0 );

	ID3D11Buffer* buffers[ 2 ];
	buffers[ 0 ] = mesh._vertex_buffer;
	buffers[ 1 ] = _instance_buffer;

	unsigned int strides[ 2 ];
	strides[ 0 ] = sizeof( Vertex );
	strides[ 1 ] = sizeof( InstanceData );
	unsigned int offsets[ 2 ];
	offsets[ 0 ] = 0;
	offsets[ 1 ] = 0;

	_device.GetRawContextPtr()->IASetVertexBuffers(
		0,
		2,
		buffers, //&mesh._vertex_buffer,
		strides,
		offsets );

	_device.GetRawContextPtr()->IASetIndexBuffer(
		mesh._index_buffer,
		DXGI_FORMAT_R32_UINT,
		0 );

	VertexShaderLocator vsl( _device.GetRawDevicePtr() );
	ID3D11VertexShader* vs =
		vsl.Request( rcd._vertex_shader_filename, rcd._vertex_shader ).Data();
	/**************************************************************************
	 * VertexShaderLocator.GetInputLayout cannot be called before successfully
	 * requesting at least one vertex shader. This is because we need a shader
	 * blob to initialize the layout. Also, right now we really only need to
	 * call it once, not once per draw, since all the shaders have the same
	 * layout. We should probably add another std::map and store input layouts
	 * per shader.
	 */
	_device.GetRawContextPtr()->IASetInputLayout( vsl.GetInputLayout() );
	_device.GetRawContextPtr()->VSSetConstantBuffers( 0, 1, &_per_frame_buffer );

	PixelShaderLocator psl( _device.GetRawDevicePtr() );
	ID3D11PixelShader* ps =
		psl.Request( rcd._pixel_shader_filename, rcd._pixel_shader ).Data();
	
	_device.GetRawContextPtr()->VSSetShader( vs, 0, 0 );
	_device.GetRawContextPtr()->PSSetShader( ps, 0, 0 );
	_device.GetRawContextPtr()->DrawIndexedInstanced( mesh._num_indices, 1, 0, 0, 0 );

	_swap_chain.Show();
}

void D3D11Renderer::ClearViewsAndRenderTargets()
{
    //clear the views
	float clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_device.GetRawContextPtr()->ClearRenderTargetView( _render_target_view, clear_color );
	_device.GetRawContextPtr()->ClearDepthStencilView( _depth_stencil_view, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0 );
}
