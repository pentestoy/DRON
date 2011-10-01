/**
 *  Display/D3D11Renderer.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef D3D11RENDERER_HPP
#define D3D11RENDERER_HPP

#include <vector>
#include <D3D11.h>
#include <xnamath.h>
#include "D3D11/DepthStencilBuffer.hpp"
#include "D3D11/DeviceContext.hpp"
#include "D3D11/GFXDevice.hpp"
#include "D3D11/RenderTarget.hpp"
#include "D3D11/SwapChain.hpp"
#include "../Entity/Entity.hpp"

struct WVP
{
	XMMATRIX	_world;
	XMMATRIX	_view;
	XMMATRIX	_proj;
};

struct DisplaySettings;
class EntitySystem;
class SwapChain;
class D3D11Renderer
{
    public:
        D3D11Renderer( HWND window, DisplaySettings& ds, EntitySystem& es );
		~D3D11Renderer();

		void Draw( std::vector< Entity >& entities, Entity camera );

        void OnResize( DisplaySettings& );
        void SetFullscreen( bool );

		template < typename T >
		class BufferMapping
		{
			public:
				BufferMapping( ID3D11Buffer*, ID3D11DeviceContext*, D3D11_MAP );
				~BufferMapping();

				void Close();
				const T* GetDataPtr() const { return static_cast< T* >( _data.pData ); }
				T* GetDataPtr() { return static_cast< T* >( _data.pData ); }

			protected:
				ID3D11DeviceContext*		_dc_ptr;
				ID3D11Buffer*				_buffer_ptr;
				D3D11_MAPPED_SUBRESOURCE	_data;
		};

    protected:
        bool InitializeBuffers();
		void BuildProjectionMatrices( const DisplaySettings& ds );

		// temporary
		unsigned int				_ps_id;
		unsigned int				_vs_id;

		GFXDevice					_device;
		DeviceContext				_context;
		SwapChain					_swap_chain;
		RenderTarget				_render_target;
		DepthStencilBuffer			_depth_stencil;

		WVP							_per_frame;
		XMFLOAT4X4					_world_mx;
		XMFLOAT4X4					_view_mx;
		XMFLOAT4X4					_perspec_mx;
		XMFLOAT4X4					_ortho_mx;

		ID3D11Buffer*				_instance_buffer;
		ID3D11Buffer*				_per_frame_buffer;

		EntitySystem&				_entity_system;
};

#endif  //D3D11RENDERER_HPP
