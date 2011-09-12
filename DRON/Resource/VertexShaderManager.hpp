/**
 *  Resource/VertexMeshManager.hpp
 *  (c) Jonathan Capps
 *  Created 12 Sept. 2011
 */

#ifndef _VERTEX_SHADER_MANAGER_HPP_
#define _VERTEX_SHADER_MANAGER_HPP_

#include <map>
#include <D3D11.h>
#include "ResourceManager.hpp"

class VertexShaderManager;
class VertexShaderResource : public Resource< ID3D11VertexShader >
{
	public:
		~VertexShaderResource();
		ID3D11VertexShader* Data() { return _data; }

		friend VertexShaderManager;
};

class VertexShaderManager : public ResourceManager< VertexShaderResource >
{
	public:
		~VertexShaderManager();

		void Initialize( ID3D11Device* device ) { _device = device; }
		virtual unsigned int LoadResource( const std::string& filename )
			{ return 0; }
		unsigned int LoadResource( const std::string& filename,
								   const std::string& shader );

	private:
		ID3DBlob* CompileVertexShaderFromFile( const std::string& filename,
											   const std::string& shader );

		ID3D11Device*	_device;
};

#endif //_VERTEX_SHADER_MANAGER_HPP_
	