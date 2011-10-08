/**
 *  Display/D3D11/SwapChain.hpp
 *  (c) Jonathan Capps
 *  Created 29 Sept. 2011
 */

#ifndef DISPLAY_DED11_SWAPCHAIN_HPP
#define DISPLAY_DED11_SWAPCHAIN_HPP

#include <Windows.h>
#include <D3D11.h>

class GFXDevice;
struct DisplaySettings;
class SwapChain
{
	public:
		SwapChain(
			GFXDevice& device,
			const DisplaySettings& ds,
			const HWND window
		);
		~SwapChain();

		void Resize( const DisplaySettings& ds );
		ID3D11Texture2D* GetBuffer() const;
		void Show();

	private:
		SwapChain( const SwapChain& );
		SwapChain& operator=( const SwapChain& );

		IDXGISwapChain* _swap_chain_ptr;
};

#endif //DISPLAY_DED11_SWAPCHAIN_HPP
