/**
 *  Resource/VertexShaderManager.hpp
 *  (c) Jonathan Capps
 *  Created 11 Sept. 2011
 */

#include "VertexShaderManager.hpp"
#include <cassert>
#include <D3Dcompiler.h>
#include <D3DX11async.h>
#include "../Utility/DXUtil.hpp"
#include "../Utility/StringHelper.hpp"

VertexShaderResource::~VertexShaderResource()
{
	DXRelease( _data );
}

VertexShaderManager::~VertexShaderManager()
{
	DXRelease( _device );
}

unsigned int VertexShaderManager::LoadResource( const std::string& filename,
												const std::string& shader )
{
#if defined ( DEBUG ) || defined (_DEBUG )
	assert( _device );
#endif

	ID3DBlob* blob = CompileVertexShaderFromFile( filename, shader );
	if( !blob )
		return 0;

	//ID3D11PixelShader* pixel_shader;
	VertexShaderResource* vsr = new VertexShaderResource();
	HR( _device->CreateVertexShader( blob->GetBufferPointer(),
		blob->GetBufferSize(), 0, &vsr->_data ) );

	_resources.insert(
		std::pair< unsigned int, VertexShaderResource* >( ++_id_count, vsr ) );

	if( !_input_layout )
		CreateInputLayout( blob );

	return _id_count;
}

ID3DBlob* VertexShaderManager::CompileVertexShaderFromFile(
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
		"vs_4_0", shader_flags, 0, 0, &shader_blob, &error_blob, 0 ) );

	return shader_blob;
}

void VertexShaderManager::CreateInputLayout( ID3DBlob* blob )
{
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	HR( _device->CreateInputLayout( ied, 1, blob->GetBufferPointer(),
		blob->GetBufferSize(), &_input_layout ) );
}

ID3D11InputLayout* VertexShaderManager::GetInputLayout() const
{
	return _input_layout;
}
