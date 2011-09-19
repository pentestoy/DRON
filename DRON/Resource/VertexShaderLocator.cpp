/**
 *  Resource/VertexShaderLocator.cpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#include "VertexShaderLocator.hpp"
#include <cassert>

VertexShaderCache VertexShaderLocator::_cache;

VertexShaderLocator::VertexShaderLocator()
{
#if defined( DEBUG ) || defined ( _DEBUG )
	assert( _cache.IsInitialized() );
#endif
}

VertexShaderLocator::VertexShaderLocator( ID3D11Device* device )
{
	_cache.Initialize( device );
}

VertexShaderResource& VertexShaderLocator::Request( const std::string& filename,
								   const std::string& shader )
{
	return _cache.Request( filename, shader );
}

