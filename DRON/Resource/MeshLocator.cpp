/**
 *  Resource/MeshLocator.cpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#include "MeshLocator.hpp"
#include "MeshCache.hpp"

MeshCache MeshLocator::_cache;

MeshResource& MeshLocator::Request( const std::string& filename )
{
	return _cache.Request( filename );
}

