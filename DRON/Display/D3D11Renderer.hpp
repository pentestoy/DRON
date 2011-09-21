/**
 *  Display/D3D11Renderer.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef D3D11RENDERER_HPP
#define D3D11RENDERER_HPP

#include <D3D11.h>
#include <xnamath.h>

struct WVP
{
	XMMATRIX	_world;
	XMMATRIX	_view;
	XMMATRIX	_proj;
};

struct TestVertex
{
	XMFLOAT3 _position;
};

struct DisplaySettings;
class D3D11Renderer
{
    public:
        D3D11Renderer( HWND, DisplaySettings& );
		~D3D11Renderer();

		void Draw();

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
		void ClearViewsAndRenderTargets();

		// temporary
		unsigned int				_ps_id;
		unsigned int				_vs_id;

		ID3D11Device*				_d3d_device;
		IDXGISwapChain*				_swap_chain_ptr;
		ID3D11DeviceContext*		_device_context;

	    ID3D11RenderTargetView*     _render_target_view;
		ID3D11Texture2D*			_depth_stencil_buffer;
		ID3D11DepthStencilView*		_depth_stencil_view;

		D3D11_VIEWPORT				_view_port;

		WVP							_per_frame;
		XMFLOAT4X4					_world_mx;
		XMFLOAT4X4					_view_mx;
		XMFLOAT4X4					_perspec_mx;
		XMFLOAT4X4					_ortho_mx;

		ID3D11Buffer*				_per_frame_buffer;
};

#endif  //D3D11RENDERER_HPP
