/**
 *  Resource/VertexShaderLocator.hpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#ifndef VERTEX_SHADER_LOCATOR_HPP
#define VERTEX_SHADER_LOCATOR_HPP

#include <string>
#include <D3D11.h>
#include "VertexShaderCache.hpp"
#include "VertexShaderResource.hpp"

class VertexShaderCache;
class VertexShaderLocator
{
	public:
		VertexShaderLocator();
		VertexShaderLocator( ID3D11Device* device );

		VertexShaderResource& Request( const std::string& filename,
					  const std::string& shader );

		ID3D11InputLayout* GetInputLayout() const { return _cache.GetInputLayout(); }

	private:
		static VertexShaderCache	_cache;
};

#endif //VERTEX_SHADER_LOCATOR_HPP
