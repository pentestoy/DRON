/**
 *  Resource/PixelShaderLocator.cpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#include "PixelShaderLocator.hpp"
#include "PixelShaderCache.hpp"
#include <cassert>

PixelShaderCache* PixelShaderLocator::_cache = 0;

PixelShaderLocator::PixelShaderLocator( GFXDevice& device )
{
	if( !_cache )
		_cache = new PixelShaderCache( device );
}

PixelShaderResource& PixelShaderLocator::Request(
	const std::string& filename,
	const std::string& shader )
{
	return _cache->Request( filename, shader );
}

PixelShaderResource* PixelShaderLocator::RequestPtr(
	const std::string& filename,
	const std::string& shader )
{
	return &_cache->Request( filename, shader );
}

void PixelShaderLocator::ShutDown()
{
	delete _cache;
	_cache = 0;
}
