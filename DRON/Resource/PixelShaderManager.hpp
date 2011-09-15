/**
 *  Resource/PixelMeshManager.hpp
 *  (c) Jonathan Capps
 *  Created 11 Sept. 2011
 */

#ifndef PIXEL_SHADER_MANAGER_HPP
#define PIXEL_SHADER_MANAGER_HPP

#include <map>
#include <D3D11.h>
#include "ResourceManager.hpp"

class PixelShaderManager;
class PixelShaderResource : public Resource< ID3D11PixelShader >
{
	public:
		~PixelShaderResource();
		ID3D11PixelShader* Data() { return _data; }

		friend PixelShaderManager;
};

class PixelShaderManager : public ResourceManager< PixelShaderResource >
{
	public:
		~PixelShaderManager();

		void Initialize( ID3D11Device* device ) { _device = device; }
		virtual unsigned int LoadResource( const std::string& filename )
			{ return 0; }
		unsigned int LoadResource( const std::string& filename,
								   const std::string& shader );

	private:
		ID3DBlob* CompilePixelShaderFromFile( const std::string& filename,
											  const std::string& shader );

		ID3D11Device*	_device;
};

#endif //PIXEL_SHADER_MANAGER_HPP
