/**
 *  Resource/PixelShader/PixelShaderLocator.hpp
 *  (c) Jonathan Capps
 *  Created 16 Sept. 2011
 */

#ifndef PIXEL_SHADER_LOCATOR_HPP
#define PIXEL_SHADER_LOCATOR_HPP

#include <map>
#include <string>
#include <D3D11.h>
#include "PixelShaderCache.hpp"
#include "PixelShaderResource.hpp"

class PixelShaderLocator
{
	public:
		PixelShaderLocator();
		PixelShaderLocator( ID3D11Device* device );

		PixelShaderResource& Request( const std::string& filename,
					  const std::string& shader );

	private:
		static PixelShaderCache	_cache;
};

#endif //PIXEL_SHADER_LOCATOR_HPP
