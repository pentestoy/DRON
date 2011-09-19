/**
 *  Resource/MeshCache.cpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#include "MeshCache.hpp"
#include <Windows.h>
#include <assimp.hpp>
#include <aiScene.h>
#include <aiPostProcess.h>
#include "MeshResource.hpp"
#include "../Utility/StringHelper.hpp"

MeshCache::MeshCache()
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
		delete ( *iter ).second->_data;
		++iter;
	}
}

MeshResource& MeshCache::Request( const std::string& filename )
{
	ResourceMap::iterator iter = _resources.find( filename );
	if( iter != _resources.end() ) return *( *iter ).second;

	MeshResource mr = Load( filename );
	return mr;
}

MeshResource& MeshCache::Load( const std::string& filename )
{
	Assimp::Importer importer;
	std::string file_and_path( "Data//Meshes//" + filename );

	const aiScene* scene_ptr = importer.ReadFile( file_and_path,
		aiProcess_JoinIdenticalVertices |
		aiProcess_MakeLeftHanded        |
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

	/**************************************************************************
	 * TODO: Need to copy the mesh data, because the Importer keeps ownership
	 *       of the scene data, and destroys it when it goes out of scope.
	 */
	MeshResource* mr_ptr = new MeshResource();
	mr_ptr->_data = scene_ptr->mMeshes[ 0 ];
	mr_ptr->SetValid( true );
	_resources.insert( std::make_pair( filename, mr_ptr ) );

	return *mr_ptr;
}
