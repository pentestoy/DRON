/**
 *  Display/D3D11/DepthStencilBuffer.hpp
 *  (c) Jonathan Capps
 *  Created 01 Oct. 2011
 */

#ifndef DISPLAY_D3D11_DEPTH_STENCIL_BUFFER_HPP
#define DISPLAY_D3D11_DEPTH_STENCIL_BUFFER_HPP

#include <D3D11.h>

class GFXDevice;
struct DisplaySettings;
class DepthStencilBuffer
{
	public:
		DepthStencilBuffer();
		~DepthStencilBuffer();

		ID3D11Texture2D*		GetBufferPtr() const { return _texture_ptr; }
		ID3D11DepthStencilView* GetViewPtr() const { return _view_ptr; }

		void Release();
		void CreateNewBufferAndView(
			GFXDevice& device,
			const DisplaySettings& ds
		);

	private:
		ID3D11Texture2D*		_texture_ptr;
		ID3D11DepthStencilView* _view_ptr;
};

#endif //DISPLAY_D3D11_DEPTH_STENCIL_BUFFER_HPP
