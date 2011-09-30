/**
 *  Display/D3D11/RenderTarget.hpp
 *  (c) Jonathan Capps
 *  Created 30 Sept. 2011
 */

#ifndef DISPLAY_D3D11_RENDER_TARGET_HPP
#define DISPLAY_D3D11_RENDER_TARGET_HPP

#include <D3D11.h>

class RenderTarget
{
	public:
		RenderTarget();
		~RenderTarget();

		ID3D11RenderTargetView* GetData();
		ID3D11RenderTargetView** GetDataAddress();
		void ReleaseData();

	private:
		ID3D11RenderTargetView* _data;
};

#endif //DISPLAY_D3D11_RENDER_TARGET_HPP
