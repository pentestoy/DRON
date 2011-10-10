/**
 *  Display/RenderBatch.hpp
 *  (c) Jonathan Capps
 *  Created 09 Oct. 2011
 */

#ifndef DISPLAY_RENDER_BATCH_HPP
#define DISPLAY_RENDER_BATCH_HPP

#include <vector>
#include "../Entity/Entity.hpp"

class InputLayoutResource;
class MeshResource;
class PixelShaderResource;
class VertexShaderResource;
struct RenderBatch
{
	MeshResource*			_mesh_res_ptr;
	InputLayoutResource*	_layout_res_ptr;
	VertexShaderResource*	_vertex_shader_res_ptr;
	PixelShaderResource*	_pixel_shader_res_ptr;
	std::vector< Entity >	_entities;
};

#endif //DISPLAY_RENDER_BATCH_HPP
