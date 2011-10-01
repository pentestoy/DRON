/**
 *  Display/D3D11/DeviceContext.hpp
 *  (c) Jonathan Capps
 *  Created 30 Sept. 2011
 */

#ifndef DISPLAY_D3D11_DEVICE_CONTEXT_HPP
#define DISPLAY_D3D11_DEVICE_CONTEXT_HPP

#include <D3D11.h>
#include "Topology.hpp"

struct DisplaySettings;
class DepthStencilBuffer;
class PixelShaderResource;
class RenderTarget;
class VertexShaderResource;
class DeviceContext
{
	public:
		DeviceContext( ID3D11DeviceContext* );
		~DeviceContext();

		void InitializeFrame( RenderTarget& rt, DepthStencilBuffer& dsb ) const;

		void SetRenderTarget(
			RenderTarget& target,
			DepthStencilBuffer& dsb
		) const;
		void SetViewport( const DisplaySettings& ds ) const;

		void SetTopology( const TOPOLOGY topology ) const;
		void SetIndexBuffer( ID3D11Buffer* buffer ) const;

		void SetVertexShader( const VertexShaderResource& resource ) const;
		void SetPixelShader( const PixelShaderResource& resource ) const;

		ID3D11DeviceContext* GetRawPtr() const { return _context_ptr; }

		template < typename T >
		void UpdateBuffer( ID3D11Buffer* buffer, T& data );

	private:
		ID3D11DeviceContext*	_context_ptr;
};

template < typename T >
void DeviceContext::UpdateBuffer( ID3D11Buffer* buffer, T& data )
{
	_context_ptr->UpdateSubresource( buffer, 0, 0, &data, 0, 0 );
}

#endif //DISPLAY_D3D11_DEVICE_CONTEXT_HPP
