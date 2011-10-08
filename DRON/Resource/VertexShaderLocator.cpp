/**
 *  Resource/VertexShaderLocator.cpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#include "VertexShaderLocator.hpp"
#include "VertexShaderCache.hpp"
#include <cassert>

VertexShaderCache* VertexShaderLocator::_cache = 0;

VertexShaderLocator::VertexShaderLocator( ID3D11Device* device )
{
	if( !_cache )
		_cache = new VertexShaderCache( device );
}

VertexShaderResource& VertexShaderLocator::Request( const std::string& filename,
								   const std::string& shader )
{
	return _cache->Request( filename, shader );
}

void VertexShaderLocator::ShutDown()
{
	delete _cache;
	_cache = 0;
}
