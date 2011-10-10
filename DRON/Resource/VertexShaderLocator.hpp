/**
 *  Resource/VertexShaderLocator.hpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#ifndef VERTEX_SHADER_LOCATOR_HPP
#define VERTEX_SHADER_LOCATOR_HPP

#include <string>
#include "InputLayoutResource.hpp"
#include "VertexShaderCache.hpp"
#include "VertexShaderResource.hpp"

class GFXDevice;
class VertexShaderCache;
class VertexShaderLocator
{
	public:
		VertexShaderLocator( GFXDevice& device );

		VertexShaderResource& Request( const std::string& filename,
					  const std::string& shader );
		VertexShaderResource* RequestPtr( const std::string& filename,
					  const std::string& shader );
		static void ShutDown();
		InputLayoutResource* GetInputLayout( VertexShaderResource* resource ) const;// { return _cache->GetInputLayout(); }

	private:
		VertexShaderLocator( const VertexShaderLocator& );
		VertexShaderLocator& operator=( const VertexShaderLocator& );

		static VertexShaderCache*	_cache;
};

#endif //VERTEX_SHADER_LOCATOR_HPP
