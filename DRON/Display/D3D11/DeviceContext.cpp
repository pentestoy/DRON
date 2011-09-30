/**
 *  Display/D3D11/DeviceContext.cpp
 *  (c) Jonathan Capps
 *  Created 30 Sept. 2011
 */

#include "DeviceContext.hpp"
#include <cassert>
#include "RenderTarget.hpp"
#include "../DisplaySettings.hpp"
#include "../../Resource/PixelShaderResource.hpp"
#include "../../Resource/VertexShaderResource.hpp"
#include "../../Utility/DXUtil.hpp"

DeviceContext::DeviceContext( ID3D11DeviceContext* context )
	: _context( context )
{ }

DeviceContext::~DeviceContext()
{
	DXRelease( _context );
}

void DeviceContext::InitializeFrame( RenderTarget& rt, ID3D11DepthStencilView* dsv ) const
{
	float clear_color[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	_context->ClearRenderTargetView( rt.GetData(), clear_color );
	_context->ClearDepthStencilView( dsv, D3D10_CLEAR_DEPTH | D3D10_CLEAR_STENCIL, 1.0f, 0 );

    // set defaults for the depth/stencil and blend states
    _context->OMSetDepthStencilState( 0, 0 );

    float bf[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    _context->OMSetBlendState( 0, bf, 0xffffffff );

	SetTopology( TOPOLOGY_TRIANGLE_LIST );
}

void DeviceContext::SetRenderTarget(
	RenderTarget& target,
	ID3D11DepthStencilView* ds_view ) const
{
	/* I think I'm going to have to support multiple render targets,
	 * so I'm going to need to rivise ths approach at some point.
	 */
	ID3D11RenderTargetView* rtv = target.GetData();
	_context->OMSetRenderTargets( 1, &rtv, ds_view );
}

void DeviceContext::SetTopology( const TOPOLOGY topology ) const
{
	/* TODO: Find a better way to translate between enums
	 *       than to use a switch statement.
	 *       I should probably use a std::map,
	 *       but where's best to put it? Hmmm....
	 */
	D3D11_PRIMITIVE_TOPOLOGY t = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;

	switch( topology )
	{
		case TOPOLOGY_TRIANGLE_LIST:
			t = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
			break;

		default:
			assert( false );
	}

	_context->IASetPrimitiveTopology( t );
}

void DeviceContext::SetViewport( const DisplaySettings& ds ) const
{
	D3D11_VIEWPORT vp;
	vp.TopLeftX = vp.TopLeftY = vp.MinDepth = 0.0f;
	vp.Width = static_cast< float >( ds._width );
	vp.Height = static_cast< float >( ds._height );
	vp.MaxDepth = 1.0f;

	/* Should I support more than one viewport? */
	_context->RSSetViewports( 1, &vp );
}

void DeviceContext::SetIndexBuffer( ID3D11Buffer* buffer ) const
{
	_context->IASetIndexBuffer( buffer, DXGI_FORMAT_R32_UINT, 0 );
}

void DeviceContext::SetVertexShader( const VertexShaderResource& resource ) const
{
	/* TODO: Research 1D3D11ClassInstance. It might be useful as things progress.
	 */
	_context->VSSetShader( resource.Data(), 0, 0 );
}

void DeviceContext::SetPixelShader( const PixelShaderResource& resource ) const
{
	_context->PSSetShader( resource.Data(), 0, 0 );
}
