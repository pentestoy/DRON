/**
 *  Display/D3D11Renderer.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef D3D11RENDERER_HPP
#define D3D11RENDERER_HPP

#include <map>
#include <string>
#include <vector>
#include <Windows.h>
#include <xnamath.h>
#include "D3D11/DataBuffer.hpp"
#include "D3D11/DepthStencilBuffer.hpp"
#include "D3D11/GFXDevice.hpp"
#include "D3D11/RenderTarget.hpp"
#include "D3D11/SwapChain.hpp"
#include "../Entity/Entity.hpp"
#include "../Utility/AlignedPtr.hpp"
#include "../Utility/Geometry.hpp"

struct ViewProj
{
	XMMATRIX	_view;
	XMMATRIX	_proj;
};

struct DisplaySettings;
struct RenderBatch;
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

    protected:
		D3D11Renderer( const D3D11Renderer& );
		D3D11Renderer& operator=( const D3D11Renderer& );

		void UpdateMatrixBuffer( Entity camera );
		void BuildBatchLists(
			std::vector< Entity >& entities,
			std::map< std::string, RenderBatch >& batches );
		void FillInstanceBuffer(
			std::vector< Entity >& entities,
			DataBuffer< InstanceData >& buffer );
		void DrawBatches(
			std::map< std::string, RenderBatch >& batches );
		XMMATRIX BuildCameraMatrix( Entity camera );
		void BuildProjectionMatrices( const DisplaySettings& ds );

		GFXDevice					_device;
		SwapChain					_swap_chain;
		RenderTarget				_render_target;
		DepthStencilBuffer			_depth_stencil;

		AlignedPtr< XMMATRIX >		_perspec_mx;
		AlignedPtr< XMMATRIX >		_ortho_mx;

		DataBuffer< ViewProj >      _per_frame_buffer;
		DataBuffer< InstanceData >  _instance_buffer;

		EntitySystem&				_entity_system;
};

#endif  //D3D11RENDERER_HPP
