/**
 *  Display/D3D11/RenderTarget.hpp
 *  (c) Jonathan Capps
 *  Created 30 Sept. 2011
 */

#include "RenderTarget.hpp"
#include "GFXDevice.hpp"
#include "SwapChain.hpp"
#include "../../Utility/DXUtil.hpp"

RenderTarget::RenderTarget()
	: _data( 0 )
{ }

RenderTarget::~RenderTarget()
{
	Release();
}

void RenderTarget::Initialize( GFXDevice& device, const SwapChain& sc )
{
	Release();
    ID3D11Texture2D* buffer = sc.GetBuffer();
    device.GetRawDevicePtr()->CreateRenderTargetView( buffer, 0, GetDataAddress() );
	DXRelease( buffer );
}

ID3D11RenderTargetView* RenderTarget::GetData()
{
	return _data;
}

ID3D11RenderTargetView** RenderTarget::GetDataAddress()
{
	return &_data;
}

void RenderTarget::Release()
{
	DXRelease( _data );
}
