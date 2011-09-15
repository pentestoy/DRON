/**
 *  Resource/VertexShaderLocator.hpp
 *  (c) Jonathan Capps
 *  Created 14 Sept. 2011
 */

#ifndef _VERTEX_SHADER_LOCATOR_HPP_
#define _VERTEX_SHADER_LOCATOR_HPP_

#include <map>
#include <string>
#include <D3D11.h>
#include "ResourceManager.hpp"

struct ID3D11VertexShader;
class VertexShaderCache;
class VertexShaderResource : public Resource< ID3D11VertexShader >
{
	public:
		virtual ~VertexShaderResource();
		ID3D11VertexShader* Data() { return _data; }

		friend VertexShaderCache;
};

class VertexShaderCache
{
	public:
		VertexShaderCache( ID3D11Device* device );
		~VertexShaderCache();
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
		std::map< std::string, VertexShaderResource* > _resources;
};

class VertexShaderLocator
{
	public:
		VertexShaderLocator( ID3D11Device* device );

		VertexShaderResource& Request( const std::string& filename,
					  const std::string& shader );

		ID3D11InputLayout* GetInputLayout() const { return _cache->GetInputLayout(); }

	private:
		static VertexShaderCache*	_cache;
};

#endif //_VERTEX_SHADER_LOCATOR_HPP_