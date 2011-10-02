/**
 *  Display/D3D11/GFXDevice.cpp
 *  (c) Jonathan Capps
 *  Created 29 Sept. 2011
 */

#include "GFXDevice.hpp"
#include <vector>
#include "RenderTarget.hpp"
#include "SwapChain.hpp"
#include"../../Utility/DXUtil.hpp"

GFXDevice::GFXDevice()
	: _device_ptr( 0 ), _device_context_ptr( 0 )
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
		&_device_context_ptr
	) );
}

GFXDevice::~GFXDevice()
{
	DXRelease( _device_ptr );
}
