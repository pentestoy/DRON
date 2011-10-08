/**
 *  Resource/VertexShaderResource.hpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#ifndef VERTEX_SHADER_RESOURCE_HPP
#define VERTEX_SHADER_RESOURCE_HPP

#include <D3D11.h>
#include "BaseResource.hpp"

class VertexShaderCache;
class VertexShaderResource : public Resource< ID3D11VertexShader >
{
	public:
		VertexShaderResource()
			: Resource< ID3D11VertexShader >()
		{ }
		virtual ~VertexShaderResource();
		ID3D11VertexShader* Data() const { return _data; }

		friend VertexShaderCache;

	private:
		VertexShaderResource( const VertexShaderResource& );
		VertexShaderResource& operator=( const VertexShaderResource& );
};

#endif //VERTEX_SHADER_RESOURCE_HPP
