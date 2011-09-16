/**
 *  Resource/VertexShader/VertexShaderCache.hpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#ifndef VERTEX_SHADER_CACHE_HPP
#define VERTEX_SHADER_CACHE_HPP

#include "../ResourceManager.hpp"
#include <D3D11.h>

class VertexShaderResource;
class VertexShaderCache
{
	public:
		VertexShaderCache();
		~VertexShaderCache();
		void Initialize( ID3D11Device* device ) { _device = device; }
		bool IsInitialized() { return _device != 0; }
		VertexShaderResource& Request( const std::string& filename,
									   const std::string& shader );

		ID3D11InputLayout* GetInputLayout() const { return _input_layout; }

	protected:
		VertexShaderResource& Load( const std::string& filename,
									const std::string& shader );

		ID3DBlob* CompileVertexShaderFromFile(
			const std::string& filename,
			const std::string& shader );

		void CreateInputLayout( ID3DBlob* );

		ID3D11Device*		_device;
		ID3D11InputLayout*	_input_layout;

		typedef std::map< std::string, VertexShaderResource* > ResourceMap;
		ResourceMap _resources;
};

#endif //VERTEX_SHADER_CACHE_HPP
