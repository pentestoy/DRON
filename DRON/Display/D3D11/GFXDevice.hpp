/**
 *  Display/D3D11/GFXDevice.hpp
 *  (c) Jonathan Capps
 *  Created 29 Sept. 2011
 */

#ifndef DISPLAY_D3D11_GFXDEVICE_HPP
#define DISPLAY_D3D11_GFXDEVICE_HPP

#include <D3D11.h>

class GFXDevice
{
	public:
		GFXDevice();
		~GFXDevice();

		ID3D11Device* GetRawDevicePtr() { return _device_ptr; }
		ID3D11DeviceContext* GetRawContextPtr() { return _device_context_ptr; }

	private:
		ID3D11Device*			_device_ptr;
		ID3D11DeviceContext*	_device_context_ptr;
};

#endif //DISPLAY_D3D11_GFXDEVICE_HPP
