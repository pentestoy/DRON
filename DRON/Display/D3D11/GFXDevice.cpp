/**
 *  Display/D3D11/GFXDevice.cpp
 *  (c) Jonathan Capps
 *  Created 29 Sept. 2011
 */

#include "GFXDevice.hpp"
#include <vector>
#include "DepthStencilBuffer.hpp"
#include "RenderTarget.hpp"
#include "SwapChain.hpp"
#include "../DisplaySettings.hpp"
#include "../../Resource/PixelShaderResource.hpp"
#include "../../Resource/VertexShaderResource.hpp"
#include "../../Utility/DXUtil.hpp"

GFXDevice::GFXDevice()
	: _device_ptr( 0 ), _context_ptr( 0 )
{
	unsigned int create_device_flags = 0;
#if defined( DEBUG ) || defined( _DEBUG )  
    create_device_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	std::vector< D3D_FEATURE_LEVEL > feature_levels;
	feature_levels.push_back( D3D_FEATURE_LEVEL_11_0 );
	feature_levels.push_back( D3D_FEATURE_LEVEL_10_1 );
	feature_levels.push_back( D3D_FEATURE_LEVEL_10_0 );

	HR( D3D11CreateDevice(
		0,
		D3D_DRIVER_TYPE_HARDWARE,
		0,
		create_device_flags,
		&feature_levels[ 0 ],
		feature_levels.size(),
		D3D11_SDK_VERSION,
		&_device_ptr,
		0,
		&_context_ptr
	) );
}

GFXDevice::~GFXDevice()
{
	_context_ptr->ClearState();
	_context_ptr->Flush();
	DXRelease( _context_ptr );
	DXRelease( _device_ptr );
}

void GFXDevice::SetRenderTargets(
	std::vector< RenderTarget* >& targets,
	DepthStencilBuffer& dsb ) const
{
	std::vector< ID3D11RenderTargetView* > views;

	std::vector< RenderTarget* >::iterator iter = targets.begin();
	while( iter != targets.end() )
	{
		views.push_back( ( *iter )->GetData() );
		++iter;
	}

	_context_ptr->OMSetRenderTargets( views.size(), &views[ 0 ], dsb.GetViewPtr() );
}

void GFXDevice::SetRenderTarget(
	RenderTarget& target,
	DepthStencilBuffer& dsb ) const
{
	//ID3D11RenderTargetView* rtv = target.GetData();
	std::vector< RenderTarget* > targets;
	targets.push_back( &target );
	SetRenderTargets( targets, dsb );
}

void GFXDevice::SetViewport( const DisplaySettings& ds ) const
{
	D3D11_VIEWPORT vp;
	vp.TopLeftX = vp.TopLeftY = vp.MinDepth = 0.0f;
	vp.Width = static_cast< float >( ds._width );
	vp.Height = static_cast< float >( ds._height );
	vp.MaxDepth = 1.0f;

	// Currently only supporting one viewport.
	_context_ptr->RSSetViewports( 1, &vp );
}

void GFXDevice::InitializeFrame(
	RenderTarget& rt,
	DepthStencilBuffer& dsb ) const
{
	float clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_context_ptr->ClearRenderTargetView( rt.GetData(), clear_color );
	_context_ptr->ClearDepthStencilView(
		dsb.GetViewPtr(),
		D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL,
		1.0f,
		0
	);

    // set defaults for the depth/stencil and blend states
    _context_ptr->OMSetDepthStencilState( 0, 0 );

    float bf[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    _context_ptr->OMSetBlendState( 0, bf, 0xffffffff );

	SetTopology( TOPOLOGY_TRIANGLE_LIST );
}

void GFXDevice::SetTopology( const TOPOLOGY topology ) const
{
	_context_ptr->IASetPrimitiveTopology(
		( D3D11_PRIMITIVE_TOPOLOGY )topology );
}

void GFXDevice::SetIndexBuffer( ID3D11Buffer* buffer ) const
{
	_context_ptr->IASetIndexBuffer( buffer, DXGI_FORMAT_R32_UINT, 0 );
}

void GFXDevice::SetVertexShader( const VertexShaderResource& resource ) const
{
	/* TODO: Research 1D3D11ClassInstance. It might be useful as things progress.
	 */
	_context_ptr->VSSetShader( resource.Data(), 0, 0 );
}

void GFXDevice::SetPixelShader( const PixelShaderResource& resource ) const
{
	_context_ptr->PSSetShader( resource.Data(), 0, 0 );
}
