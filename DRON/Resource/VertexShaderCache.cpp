/**
 *  Resource/VertexShaderCache.cpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#include "VertexShaderCache.hpp"
#include <cassert>
#include <D3Dcompiler.h>
#include <D3DX11async.h>
#include "InputLayoutResource.hpp"
#include "VertexShaderResource.hpp"
#include "../Display/D3D11/GFXDevice.hpp"
#include "../Utility/DXUtil.hpp"
#include "../Utility/StringHelper.hpp"

VertexShaderCache::VertexShaderCache( GFXDevice& device )
	: _device( device ) //, _input_layout( 0 )
{
	VertexShaderResource* invalid_shader = new VertexShaderResource();
	invalid_shader->SetValid( false );
	_resources.insert(
		std::make_pair( "invalid_resource", invalid_shader ) );

	InputLayoutResource* invalid_layout = new InputLayoutResource();
	_layouts.insert(
		std::make_pair(
			reinterpret_cast< VertexShaderResource* >( 0 ),
			invalid_layout )
	);
}

VertexShaderCache::~VertexShaderCache()
{
	ResourceMap::iterator r_iter = _resources.begin();
	while( r_iter != _resources.end() )
	{
		delete ( *r_iter ).second;
		++r_iter;
	}

	LayoutMap::iterator l_iter = _layouts.begin();
	while( l_iter != _layouts.end() )
	{
		delete ( *l_iter ).second;
		++l_iter;
	}
}

VertexShaderResource& VertexShaderCache::Request( const std::string& filename,
												  const std::string& shader )
{
	std::string key( filename + shader );
	ResourceMap::iterator iter = 
		_resources.find( key );

	if( iter != _resources.end() ) return *( *iter ).second;

	return Load( filename, shader );
}

InputLayoutResource* VertexShaderCache::GetInputLayout(
	VertexShaderResource* resource ) const
{
	LayoutMap::const_iterator m_iter = _layouts.find( resource );
	if( m_iter == _layouts.end() )
		return ( *_layouts.find( 0 ) ).second;

	return ( *m_iter ).second;
}

VertexShaderResource& VertexShaderCache::Load( const std::string& filename,
											   const std::string& shader )
{
	ID3DBlob* blob = CompileVertexShaderFromFile( filename, shader );
	if( !blob )
		return *( *_resources.find( "invalid_resource" ) ).second;

	VertexShaderResource* vsr_ptr = new VertexShaderResource();
	/**************************************************************************
	 * TODO: Get rid of this raw D3D11Device call.
	 */
	HR( _device.GetRawDevicePtr()->CreateVertexShader( blob->GetBufferPointer(),
		blob->GetBufferSize(), 0, &vsr_ptr->_data ) );
	vsr_ptr->SetValid( true );

	std::string key( filename + shader );
	_resources.insert( std::make_pair( key, vsr_ptr ) );

	CreateInputLayout( vsr_ptr, blob );

	return *( *_resources.find( key ) ).second;
}

ID3DBlob* VertexShaderCache::CompileVertexShaderFromFile(
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

void VertexShaderCache::CreateInputLayout(
	VertexShaderResource* resource,
	ID3DBlob* blob )
{
	/**************************************************************************
	 * TODO: Gotta be a better way to populate this vector.
	 */
	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT,    0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA,   0 },
		{ "Transform", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "Transform", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "Transform", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "Transform", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
		{ "COLOR",     0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
	};
	
	std::vector< D3D11_INPUT_ELEMENT_DESC > ied_list;
	for( unsigned int count = 0; count < 6; ++count )
		ied_list.push_back( ied[ count ] );

	InputLayoutResource* layout = new InputLayoutResource( _device, ied_list, blob );
	_layouts.insert( std::make_pair( resource, layout ) );
	/**************************************************************************
	 * TODO: Get rid of this raw D3D11Device call.
	 */
	//HR( _device.GetRawDevicePtr()->CreateInputLayout( ied, 6, blob->GetBufferPointer(),
	//	blob->GetBufferSize(), &_input_layout ) );
}
