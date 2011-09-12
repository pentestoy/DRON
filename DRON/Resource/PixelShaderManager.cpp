/**
 *  Resource/PixelMeshManager.hpp
 *  (c) Jonathan Capps
 *  Created 11 Sept. 2011
 */

#include "PixelShaderManager.hpp"
#include <cassert>
#include <D3Dcompiler.h>
#include <D3DX11async.h>
#include "../Utility/DXUtil.hpp"
#include "../Utility/StringHelper.hpp"

PixelShaderResource::~PixelShaderResource()
{
	DXRelease( _data );
}

PixelShaderManager::~PixelShaderManager()
{
	DXRelease( _device );
}

unsigned int PixelShaderManager::LoadResource( const std::string& filename,
											   const std::string& shader )
{
#if defined ( DEBUG ) || defined (_DEBUG )
	assert( _device );
#endif

	ID3DBlob* blob = CompilePixelShaderFromFile( filename, shader );
	if( !blob )
		return 0;

	//ID3D11PixelShader* pixel_shader;
	PixelShaderResource* psr = new PixelShaderResource();
	HR( _device->CreatePixelShader( blob->GetBufferPointer(),
		blob->GetBufferSize(), 0, &psr->_data ) );

	_resources.insert(
		std::pair< unsigned int, PixelShaderResource* >( ++_id_count, psr ) );

	return _id_count;
}

ID3DBlob* PixelShaderManager::CompilePixelShaderFromFile(
	const std::string& filename,
	const std::string& shader )
{
	DWORD shader_flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	shader_flags |= D3DCOMPILE_DEBUG;
#endif

	std::wstring wfilename = std::wstring( L"Data//Shaders//" )
						   + StringToWString( filename );
	ID3D10Blob* shader_blob = 0;
	ID3D10Blob* error_blob = 0;
	HR( D3DX11CompileFromFile( wfilename.c_str(), 0, 0, shader.c_str(),
		"ps_4_0", shader_flags, 0, 0, &shader_blob, &error_blob, 0 ) );

	return shader_blob;
}