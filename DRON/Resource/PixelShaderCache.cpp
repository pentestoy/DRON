/**
 *  Resource/PixelShaderCache.cpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#include "PixelShaderCache.hpp"
#include <cassert>
#include <D3Dcompiler.h>
#include <D3DX11async.h>
#include "PixelShaderResource.hpp"
#include "../Utility/DXUtil.hpp"
#include "../Utility/StringHelper.hpp"

PixelShaderCache::PixelShaderCache()
	: _device( 0 )
{
	PixelShaderResource* invalid_resource = new PixelShaderResource();
	invalid_resource->SetValid( false );
	_resources.insert(
		std::make_pair( "invalid_resource", invalid_resource ) );
}

PixelShaderCache::~PixelShaderCache()
{
	ResourceMap::iterator iter = _resources.begin();
	while( iter != _resources.end() )
	{
		DXRelease( ( *iter ).second->_data );
		++iter;
	}
}

PixelShaderResource& PixelShaderCache::Request( const std::string& filename,
												const std::string& shader )
{
	std::string key( filename + shader );
	ResourceMap::iterator iter = _resources.find( key );

	if( iter != _resources.end() ) return *( *iter ).second;

	return Load( filename, shader );
}

PixelShaderResource& PixelShaderCache::Load( const std::string& filename,
											 const std::string& shader )
{
#if defined ( DEBUG ) || defined (_DEBUG )
	assert( _device );
#endif

	ID3DBlob* blob = CompilePixelShaderFromFile( filename, shader );
	if( !blob )
		return *( *_resources.find( "invalid_resource" ) ).second;

	PixelShaderResource* psr_ptr = new PixelShaderResource();
	HR( _device->CreatePixelShader( blob->GetBufferPointer(),
		blob->GetBufferSize(), 0, &psr_ptr->_data ) );
	psr_ptr->SetValid( true );

	std::string key( filename + shader );
	_resources.insert( std::make_pair( key, psr_ptr ) );

	return *( *_resources.find( key ) ).second;
}

ID3DBlob* PixelShaderCache::CompilePixelShaderFromFile(
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
