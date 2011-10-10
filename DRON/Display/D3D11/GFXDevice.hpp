/**
 *  Display/D3D11/GFXDevice.hpp
 *  (c) Jonathan Capps
 *  Created 29 Sept. 2011
 */

#ifndef DISPLAY_D3D11_GFXDEVICE_HPP
#define DISPLAY_D3D11_GFXDEVICE_HPP

#include <D3D11.h>
#include <vector>
#include "Topology.hpp"

struct DisplaySettings;
class D3D11Renderer;
class DepthStencilBuffer;
class InputLayoutResource;
class PixelShaderResource;
class RenderTarget;
class SwapChain;
class VertexShaderResource;
class GFXDevice
{
	public:
		GFXDevice();
		~GFXDevice();

		ID3D11Device* GetRawDevicePtr() { return _device_ptr; }
		ID3D11DeviceContext* GetRawContextPtr() { return _context_ptr; }

		void SetRenderTargets(
			std::vector< RenderTarget* >& targets,
			DepthStencilBuffer& dsb
		) const;
		void SetRenderTarget(
			RenderTarget& target,
			DepthStencilBuffer& dsb
		) const;
		void SetViewport( const DisplaySettings& ds ) const;
		void InitializeFrame( RenderTarget& rt, DepthStencilBuffer& dsb ) const;

		template < typename T >
		void UpdateBuffer( ID3D11Buffer* buffer, T& data );

		void SetIndexBuffer( ID3D11Buffer* buffer ) const;
		void SetVertexShader( const VertexShaderResource* resource ) const;
		void SetPixelShader( const PixelShaderResource* resource ) const;
		void SetInputLayout( const InputLayoutResource* layout ) const;

	private:
		GFXDevice( const GFXDevice& );
		GFXDevice& operator=( const GFXDevice& );

		void SetTopology( const TOPOLOGY topology ) const;

		ID3D11Device*			_device_ptr;
		ID3D11DeviceContext*	_context_ptr;
};

template < typename T >
void GFXDevice::UpdateBuffer( ID3D11Buffer* buffer, T& data )
{
	_context_ptr->UpdateSubresource( buffer, 0, 0, &data, 0, 0 );
}

#endif //DISPLAY_D3D11_GFXDEVICE_HPP
