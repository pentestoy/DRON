/**
 *  Resource/MeshCache.cpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#include "MeshCache.hpp"

#if defined( DEBUG ) || defined( _DEBUG )  
#include <sstream>
#endif

#include <Windows.h>
#include <D3D11.h>
#include <D3Dcommon.h>
#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include "MeshResource.hpp"
#include "../Display/D3D11/GFXDevice.hpp"
#include "../Utility/DXUtil.hpp"
#include "../Utility/Geometry.hpp"
#include "../Utility/StringHelper.hpp"

MeshCache::MeshCache( GFXDevice& device )
	: _device( device )
{
	MeshResource* invalid_resource = new MeshResource();
	invalid_resource->SetValid( false );
	_resources.insert(
		std::make_pair( "invalid_resource", invalid_resource ) );
}

MeshCache::~MeshCache()
{
	ResourceMap::iterator iter = _resources.begin();
	while( iter != _resources.end() )
	{
		delete ( *iter ).second;
		++iter;
	}
}

MeshResource& MeshCache::Request( const std::string& filename )
{
	ResourceMap::iterator iter = _resources.find( filename );
	if( iter != _resources.end() ) return *( *iter ).second;

	MeshResource& mr = Load( filename );
	return mr;
}

MeshResource& MeshCache::Load( const std::string& filename )
{
	Assimp::Importer importer;
	std::string file_and_path( "Data//Meshes//" + filename );

	const aiScene* scene_ptr = importer.ReadFile( file_and_path,
		aiProcess_JoinIdenticalVertices |
		aiProcess_GenSmoothNormals      |
		aiProcess_Triangulate           |
		aiProcess_ImproveCacheLocality  |
		aiProcess_SortByPType           |
		aiProcess_OptimizeMeshes        |
		aiProcess_OptimizeGraph );

	if( !scene_ptr )
	{
		std::wstring ws = StringToWString( importer.GetErrorString() );
		OutputDebugString( ws.c_str() );

		return *( *_resources.find( "invalid_resource" ) ).second;
	}

	if( !scene_ptr->HasMeshes() )
	{
		OutputDebugString( L"The scene has no meshes!" );
		return *( *_resources.find( "invalid_resource" ) ).second;
	}

	MeshResource* mr_ptr = new MeshResource();
	mr_ptr->_data = BuildMesh( scene_ptr, filename );
	mr_ptr->SetValid( true );
	_resources.insert( std::make_pair( filename, mr_ptr ) );

	return *mr_ptr;
}

Mesh* MeshCache::BuildMesh( const aiScene* scene_ptr, const std::string& filename )
{
	aiMesh* ai_mesh_ptr = scene_ptr->mMeshes[ 0 ];
	Mesh* mesh = new Mesh;

	aiNode* node_ptr = scene_ptr->mRootNode;

	XMMATRIX xform = AIMatrixToXMMatrix( node_ptr->mTransformation );
	xform = XMMatrixTranspose( xform );
	std::vector< XMFLOAT3 > vertices;

	for( unsigned int i = 0; i < ai_mesh_ptr->mNumVertices; ++i )
	{
		aiVector3D v = ai_mesh_ptr->mVertices[ i ];
		XMVECTOR vert = XMVectorSet( v.x, v.y, v.z, 0.0f );
		vert = XMVector3Transform( vert, xform );
		XMFLOAT3 final;
		XMStoreFloat3( &final, vert );
		vertices.push_back( final );
	}
		 
    D3D11_BUFFER_DESC bd;
	bd.ByteWidth = sizeof( aiVector3D ) * ai_mesh_ptr->mNumVertices;
    bd.Usage = D3D11_USAGE_IMMUTABLE;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA dsd;
	ZeroMemory( &dsd, sizeof( dsd ) );
	dsd.pSysMem = &vertices[ 0 ];

	/**************************************************************************
	 * TODO: Change this to not require a raw call to the D3D11Device.
	 */
	HR( _device.GetRawDevicePtr()->CreateBuffer( &bd, &dsd, &mesh->_vertex_buffer ) );

#if defined( DEBUG ) || defined( _DEBUG )  
	std::stringstream ss;
	ss << "VB " << filename;
	mesh->_vertex_buffer->SetPrivateData(
		WKPDID_D3DDebugObjectName,
		ss.str().size(),
		ss.str().c_str() );
#endif

	mesh->_num_vertices = ai_mesh_ptr->mNumVertices;

	std::vector< unsigned int > index_vector;
	index_vector.reserve( ai_mesh_ptr->mNumFaces * 3 );

	for( unsigned int i = 0; i < ai_mesh_ptr->mNumFaces; ++i )
	{
		index_vector.push_back( ai_mesh_ptr->mFaces[ i ].mIndices[ 0 ] );
		index_vector.push_back( ai_mesh_ptr->mFaces[ i ].mIndices[ 1 ] );
		index_vector.push_back( ai_mesh_ptr->mFaces[ i ].mIndices[ 2 ] );
	}

	bd.ByteWidth = sizeof( unsigned int ) * ai_mesh_ptr->mNumFaces * 3;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	dsd.pSysMem = &index_vector[ 0 ];

	/**************************************************************************
	 * TODO: Change this to not require a raw call to the D3D11Device.
	 */
	HR( _device.GetRawDevicePtr()->CreateBuffer( &bd, &dsd, &mesh->_index_buffer ) );

#if defined( DEBUG ) || defined( _DEBUG )  
	ss.str("");
	ss << "IB " << filename;
	mesh->_index_buffer->SetPrivateData(
		WKPDID_D3DDebugObjectName,
		ss.str().size(),
		ss.str().c_str() );
#endif

	mesh->_num_indices = ai_mesh_ptr->mNumFaces * 3;

	return mesh;
}
