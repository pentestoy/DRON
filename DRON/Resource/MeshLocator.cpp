/**
 *  Resource/MeshLocator.cpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#include "MeshLocator.hpp"
#include <cassert>
#include "MeshCache.hpp"

MeshCache* MeshLocator::_cache = 0;

MeshLocator::MeshLocator()
{
	assert( _cache );
}

MeshLocator::MeshLocator( GFXDevice& device )
{
	if( !_cache )
		_cache = new MeshCache( device );
}

MeshResource& MeshLocator::Request( const std::string& filename )
{
	return _cache->Request( filename );
}

MeshResource* MeshLocator::RequestPtr( const std::string& filename )
{
	return &_cache->Request( filename );
}

void MeshLocator::ShutDown()
{
	delete _cache;
	_cache = 0;
}

