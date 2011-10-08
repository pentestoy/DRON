/**
 *  Resource/PixelShaderResource.hpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#ifndef PIXEL_SHADER_RESOURCE_HPP
#define PIXEL_SHADER_RESOURCE_HPP

#include <D3D11.h>
#include "BaseResource.hpp"

class PixelShaderCache;
class PixelShaderResource : public Resource< ID3D11PixelShader >
{
	public:
		PixelShaderResource()
			: Resource< ID3D11PixelShader >() { }
		virtual ~PixelShaderResource();
		ID3D11PixelShader* Data() const { return _data; }

		friend PixelShaderCache;

	private:
		PixelShaderResource( const PixelShaderResource& );
		PixelShaderResource& operator=( const PixelShaderResource& );
};

#endif //PIXEL_SHADER_RESOURCE_HPP
