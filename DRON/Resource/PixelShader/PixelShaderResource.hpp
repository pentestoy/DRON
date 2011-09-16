/**
 *  Resource/PixelShaderResource.hpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#ifndef PIXEL_SHADER_RESOURCE_HPP
#define PIXEL_SHADER_RESOURCE_HPP

#include "../ResourceManager.hpp"
#include <D3D11.h>

class PixelShaderCache;
class PixelShaderResource : public Resource< ID3D11PixelShader >
{
	public:
		virtual ~PixelShaderResource();
		ID3D11PixelShader* Data() { return _data; }

		friend PixelShaderCache;
};

#endif //PIXEL_SHADER_RESOURCE_HPP
