/**
 *  Resource/PixelShaderCache.hpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#ifndef PIXEL_SHADER_CACHE_HPP
#define PIXEL_SHADER_CACHE_HPP

#include <map>
#include <string>
#include <D3D11.h>

class PixelShaderResource;
class PixelShaderCache
{
	public:
		PixelShaderCache();
		~PixelShaderCache();
		void Initialize( ID3D11Device* device ) { _device = device; }
		bool IsInitialized() { return _device != 0; }
		PixelShaderResource& Request( const std::string& filename,
									   const std::string& shader );

	protected:
		PixelShaderResource& Load( const std::string& filename,
									const std::string& shader );

		ID3DBlob* CompilePixelShaderFromFile(
			const std::string& filename,
			const std::string& shader );

		ID3D11Device*		_device;

		typedef std::map< std::string, PixelShaderResource* > ResourceMap;
		ResourceMap _resources;
};

#endif //PIXEL_SHADER_CACHE_HPP
