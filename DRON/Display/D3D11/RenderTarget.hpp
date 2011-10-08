/**
 *  Display/D3D11/RenderTarget.hpp
 *  (c) Jonathan Capps
 *  Created 30 Sept. 2011
 */

#ifndef DISPLAY_D3D11_RENDER_TARGET_HPP
#define DISPLAY_D3D11_RENDER_TARGET_HPP

#include <D3D11.h>

class GFXDevice;
class SwapChain;
class RenderTarget
{
	public:
		RenderTarget();
		~RenderTarget();

		void Initialize( GFXDevice& device, const SwapChain& sc );
		ID3D11RenderTargetView* GetData();
		ID3D11RenderTargetView** GetDataAddress();
		void Release();

	private:
		RenderTarget( const RenderTarget& );
		RenderTarget& operator=( const RenderTarget& );

		ID3D11RenderTargetView* _data;
};

#endif //DISPLAY_D3D11_RENDER_TARGET_HPP
