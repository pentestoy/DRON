/**
 *  Engine/Display/D3D11Renderer.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include "D3D11Renderer.hpp"

#include <LinearMath/btAlignedObjectArray.h>
#include <aiMesh.h>

#include "DisplaySettings.hpp"
#include "RenderBatch.hpp"
#include "D3D11/Topology.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/CameraComponent.hpp"
#include "../Entity/Components/RenderableComponent.hpp"
#include "../Entity/Components/XformComponent.hpp"
#include "../Resource/MeshLocator.hpp"
#include "../Resource/PixelShaderLocator.hpp"
#include "../Resource/VertexShaderLocator.hpp"
#include "../Utility/DXUtil.hpp"
#include "../Utility/Geometry.hpp"

D3D11Renderer::D3D11Renderer( HWND window,
							  DisplaySettings& ds,
							  EntitySystem& es )
    : _device(), _swap_chain( _device, ds, window ), _entity_system( es ),
	  _perspec_mx(), _ortho_mx(),
	  _instance_buffer( _device, DATA_BUFFER_ACCESS_WRITE,
		DATA_BUFFER_BIND_VERTEX_BUFFER, DATA_BUFFER_USAGE_DYNAMIC, 144 ),
	  _per_frame_buffer( _device, DATA_BUFFER_ACCESS_WRITE,
		DATA_BUFFER_BIND_CONSTANT_BUFFER, DATA_BUFFER_USAGE_DYNAMIC, 1 )
{
	_perspec_mx.ResetWithDefault();
	_ortho_mx.ResetWithDefault();

    OnResize( ds );
}

D3D11Renderer::~D3D11Renderer()
{
	MeshLocator::ShutDown();
	PixelShaderLocator::ShutDown();
	VertexShaderLocator::ShutDown();
}

void D3D11Renderer::OnResize( DisplaySettings& ds )
{
	/* TODO: I may be able to move this call to the beginning of
	 *       DepthStencilBuffer::CreateNewBufferAndView()
	 *       but I can't test it until I re-implement resizing.
	 */
	_depth_stencil.Release();

	// Resize the swap chain and recreate the render target view.
	_swap_chain.Resize( ds );
	_render_target.Initialize( _device, _swap_chain );

	// Create the depth/stencil buffer and view.
	_depth_stencil.Initialize( _device, ds );

	// Bind the render target view and depth/stencil view to the pipeline.
	_device.SetRenderTarget( _render_target, _depth_stencil );
	_device.SetViewport( ds );

	BuildProjectionMatrices( ds );

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

void D3D11Renderer::Draw( std::vector< Entity >& entities, Entity camera )
{
	_device.InitializeFrame( _render_target, _depth_stencil );
	UpdateMatrixBuffer( camera );

	std::map< std::string, RenderBatch > batches;
	BuildBatchLists( entities, batches );
	DrawBatches( batches );

	_swap_chain.Show();
}

void D3D11Renderer::UpdateMatrixBuffer( Entity camera )
{
	XMMATRIX view_mx = BuildCameraMatrix( camera );

	btAlignedObjectArray< ViewProj > vp_array;
	ViewProj per_frame;
	per_frame._view  = XMMatrixTranspose( view_mx );
	per_frame._proj  = XMMatrixTranspose( *_perspec_mx );
	vp_array.push_back( per_frame );
	_per_frame_buffer.CopyDataToBuffer(
		_device,
		vp_array,
		DATA_BUFFER_MAP_WRITE_DISCARD );

}

void D3D11Renderer::BuildBatchLists(
	std::vector< Entity >& entities,
	std::map< std::string, RenderBatch >& batches )
{
	batches.clear();
	std::vector< Entity >::iterator e_iter = entities.begin();
	while( e_iter != entities.end() )
	{
		RenderableComponent::Data* rcd_ptr =
			static_cast< RenderableComponent::Data* >(
				_entity_system.GetComponentData( *e_iter, COMPONENT_RENDERABLE ) );
		if( rcd_ptr ) 
		{
			/* TODO: Right now, we're just sorting by mesh name. That will
			 *       likely have to change at some point.
			 */
			/* If the entry has already been created then its entities vector
			 * won't be empty.
			 */
			std::string key = rcd_ptr->_mesh_name;
			if( batches[ key ]._entities.size() == 0 )
			{
				MeshLocator ml( _device );
				VertexShaderLocator vsl( _device );
				PixelShaderLocator psl( _device );
				batches[ key ]._mesh_res_ptr =
					ml.RequestPtr( rcd_ptr->_mesh_name );
				batches[ key ]._vertex_shader_res_ptr =
					vsl.RequestPtr(
						rcd_ptr->_vertex_shader_filename,
						rcd_ptr->_vertex_shader
					);
				batches[ key ]._layout_res_ptr =
					vsl.GetInputLayout( batches[ key ]._vertex_shader_res_ptr );
				batches[ rcd_ptr->_mesh_name ]._pixel_shader_res_ptr =
					psl.RequestPtr(
						rcd_ptr->_pixel_shader_filename,
						rcd_ptr->_pixel_shader
					);
			}
			batches[ rcd_ptr->_mesh_name ]._entities.push_back( *e_iter );
			MeshLocator ml( _device );
		}
		++e_iter;
	}
}

void D3D11Renderer::DrawBatches(
	std::map< std::string, RenderBatch >& batches )
{
	std::map< std::string, RenderBatch >::iterator batch_iter =
		batches.begin();

	while( batch_iter != batches.end() )
	{
		RenderBatch& batch = batch_iter->second;
		std::vector< Entity >& entities = batch._entities;

		_device.SetInputLayout( batch._layout_res_ptr );
		ID3D11Buffer* constant_buffer = _per_frame_buffer.GetBuffer();
		_device.GetRawContextPtr()->VSSetConstantBuffers( 0, 1, &constant_buffer );

		FillInstanceBuffer( entities, _instance_buffer );

		Mesh* mesh = batch._mesh_res_ptr->Data();
		ID3D11Buffer* buffers[ 2 ];
		buffers[ 0 ] = mesh->_vertex_buffer;
		buffers[ 1 ] = _instance_buffer.GetBuffer();

		unsigned int strides[ 2 ];
		strides[ 0 ] = sizeof( Vertex );
		strides[ 1 ] = sizeof( InstanceData );
		unsigned int offsets[ 2 ];
		offsets[ 0 ] = 0;
		offsets[ 1 ] = 0;

		_device.GetRawContextPtr()->IASetVertexBuffers(
			0,
			2,
			buffers,
			strides,
			offsets );

		_device.SetIndexBuffer( mesh->_index_buffer );
	
		_device.SetVertexShader( batch._vertex_shader_res_ptr );
		_device.SetPixelShader( batch._pixel_shader_res_ptr );

		_device.GetRawContextPtr()->DrawIndexedInstanced( mesh->_num_indices, entities.size(), 0, 0, 0 );
		++batch_iter;
	}
}

void D3D11Renderer::FillInstanceBuffer(
	std::vector< Entity >& entities,
	DataBuffer< InstanceData >& buffer )
{
	std::vector< Entity >::iterator e_iter = entities.begin();
	btAlignedObjectArray< InstanceData > id_array;

	while( e_iter != entities.end() )
	{
		XformComponent::Data* xcd_ptr =
			static_cast< XformComponent::Data* >(
				_entity_system.GetComponentData( *e_iter, COMPONENT_XFORM ) );

		InstanceData id;
		XMVECTOR translation = xcd_ptr->_position;
		XMVECTOR rotation    = xcd_ptr->_rotation;
		XMVECTOR scale       = xcd_ptr->_scale;
		XMVECTOR rot_origin  = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
		id._xform = XMMatrixAffineTransformation(
			scale,
			rot_origin,
			rotation,
			translation );

		RenderableComponent::Data* rcd_ptr = static_cast< RenderableComponent::Data* >(
			_entity_system.GetComponentData( *e_iter, COMPONENT_RENDERABLE ) );
		id._color = rcd_ptr->_color;

		id_array.push_back( id );
		++e_iter;
	}

	_instance_buffer.CopyDataToBuffer(
		_device,
		id_array,
		DATA_BUFFER_MAP_WRITE_DISCARD );
}

XMMATRIX D3D11Renderer::BuildCameraMatrix( Entity camera )
{
	CameraComponent::Data* ccd_ptr = static_cast< CameraComponent::Data* >(
		_entity_system.GetComponentData( camera, COMPONENT_CAMERA ) );
	assert( ccd_ptr );

	XMMATRIX matrix = XMMatrixLookAtLH(
		ccd_ptr->_position,
		ccd_ptr->_lookat,
		ccd_ptr->_up );

	return matrix;
}

void D3D11Renderer::BuildProjectionMatrices( const DisplaySettings& ds )
{
	*_perspec_mx = XMMatrixPerspectiveFovLH(
		0.25f * XM_PI,
		static_cast< float >( ds._width ) / static_cast< float >( ds._height ),
		0.1f,
		100.0f );

	*_ortho_mx = XMMatrixOrthographicLH(
		static_cast< float >( ds._width ) / 16.0f,
		static_cast< float >( ds._height ) / 16.0f,
		1.0f,
		100.0f );
}
