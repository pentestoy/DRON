/**
 *  Resource/PixelShaderLocator.cpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#include "PixelShaderLocator.hpp"
#include <cassert>

PixelShaderCache PixelShaderLocator::_cache;

PixelShaderLocator::PixelShaderLocator()
{
#if defined( DEBUG ) || defined ( _DEBUG )
	assert( _cache.IsInitialized() );
#endif
}

PixelShaderLocator::PixelShaderLocator( ID3D11Device* device )
{
	_cache.Initialize( device );
}

PixelShaderResource& PixelShaderLocator::Request(
	const std::string& filename,
	const std::string& shader )
{
	return _cache.Request( filename, shader );
}

