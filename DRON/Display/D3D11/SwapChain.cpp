/**
 *  Display/D3D11/SwapChain.hpp
 *  (c) Jonathan Capps
 *  Created 29 Sept. 2011
 */

#include "SwapChain.hpp"
#include "GFXDevice.hpp"
#include "../DisplaySettings.hpp"
#include "../../Utility/DXUtil.hpp"

SwapChain::SwapChain(
	GFXDevice& device,
	const DisplaySettings& ds,
	HWND window )
	: _swap_chain_ptr( 0 )
{
	//we need to get the IDXGIFactory object
	//that was used to create the ID3D11Device
	IDXGIDevice* dxgi_device_ptr = 0;
	HR( device.GetRawDevicePtr()->QueryInterface(
			__uuidof( IDXGIDevice ),
			reinterpret_cast< void** >( &dxgi_device_ptr)
	) );
      
	IDXGIAdapter* dxgi_adapter = 0;
	HR( dxgi_device_ptr->GetParent(
			__uuidof( IDXGIAdapter ),
			reinterpret_cast< void** >( &dxgi_adapter)
	) );

	IDXGIFactory* dxgi_factory_ptr = 0;
	HR( dxgi_adapter->GetParent(
			__uuidof( IDXGIFactory ),
			reinterpret_cast< void** >( &dxgi_factory_ptr )
	) );

	DXGI_SWAP_CHAIN_DESC scd;
	scd.BufferDesc.Width  = ds._width;
	scd.BufferDesc.Height = ds._height;
	scd.BufferDesc.RefreshRate.Numerator = 60;
	scd.BufferDesc.RefreshRate.Denominator = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.SampleDesc.Count   = 1;
	scd.SampleDesc.Quality = 0;
	scd.BufferUsage  = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	scd.BufferCount  = 1;
	scd.OutputWindow = window;
	scd.Windowed     = true;
	scd.SwapEffect   = DXGI_SWAP_EFFECT_DISCARD;
	scd.Flags        = 0;

	HR( dxgi_factory_ptr->CreateSwapChain(
			device.GetRawDevicePtr(), &scd, &_swap_chain_ptr ) );
	
	DXRelease( dxgi_device_ptr );
	DXRelease( dxgi_adapter );
	DXRelease( dxgi_factory_ptr );
}

SwapChain::~SwapChain()
{
	DXRelease( _swap_chain_ptr );
}

void SwapChain::Resize( const DisplaySettings& ds )
{
	_swap_chain_ptr->ResizeBuffers( 1, ds._width, ds._height, DXGI_FORMAT_R8G8B8A8_UNORM, 0 );
}

ID3D11Texture2D* SwapChain::GetBuffer() const
{
	ID3D11Texture2D* res;
	HR( _swap_chain_ptr->GetBuffer( 0, __uuidof( ID3D11Texture2D ), reinterpret_cast< void** >( &res ) ) );

	return res;
}

void SwapChain::Show()
{
	// TODO: Look into switching to Present1().
	_swap_chain_ptr->Present( 0, 0 );
}
