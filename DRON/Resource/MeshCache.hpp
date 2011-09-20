/**
 *  Resource/MeshCache.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef MESH_CACHE_HPP
#define MESH_CACHE_HPP

#include <map>
#include <string>

struct aiScene;
struct ID3D11Device;
struct Mesh;
class MeshResource;
class MeshCache
{
	public:
		MeshCache();
		~MeshCache();

		void Initialize( ID3D11Device* device );
		MeshResource& Request( const std::string& filename );

	private:
		MeshResource& Load( const std::string& filename );
		Mesh* BuildMesh( const aiScene* scene );

		ID3D11Device*	_device;

		typedef std::map< std::string, MeshResource* > ResourceMap;
		ResourceMap		_resources;
};

#endif //MESH_CACHE_HPP
