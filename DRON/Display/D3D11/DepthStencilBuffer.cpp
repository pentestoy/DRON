/**
 *  Display/D3D11/DepthStencilBuffer.cpp
 *  (c) Jonathan Capps
 *  Created 01 Oct. 2011
 */

#include "DepthStencilBuffer.hpp"
#include "GFXDevice.hpp"
#include "../DisplaySettings.hpp"
#include "../../Utility/DXUtil.hpp"

DepthStencilBuffer::DepthStencilBuffer()
	: _texture_ptr( 0 ), _view_ptr( 0 )
{ }

DepthStencilBuffer::~DepthStencilBuffer()
{
	Release();
}

void DepthStencilBuffer::CreateNewBufferAndView(
	GFXDevice& device,
	const DisplaySettings& ds )
{
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

	ID3D11Device* device_ptr = device.GetRawDevicePtr();

    device_ptr->CreateTexture2D(&dsd, 0, &_texture_ptr);
    device_ptr->CreateDepthStencilView(_texture_ptr, 0, &_view_ptr);
}

void DepthStencilBuffer::Release()
{
	DXRelease( _texture_ptr );
	DXRelease( _view_ptr );
}
