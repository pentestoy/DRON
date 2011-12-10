/**
 *  Resource/MeshCache.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef MESH_CACHE_HPP
#define MESH_CACHE_HPP

#include <map>
#include <string>
#include <vector>
#include "../Entity/Entity.hpp"

struct aiScene;
struct Mesh;
class GFXDevice;
class MeshResource;
class MeshCache
{
	public:
		MeshCache( GFXDevice& device );
		~MeshCache();

		MeshResource& Request( const std::string& filename );

	private:
		MeshCache( const MeshCache& );
		MeshCache& operator=( const MeshCache& );

		MeshResource& Load( const std::string& filename );
		Mesh* BuildMesh( const aiScene* scene, const std::string& filename );

		GFXDevice&		_device;

		typedef std::map< std::string, MeshResource* > ResourceMap;
		ResourceMap		_resources;
};

#endif //MESH_CACHE_HPP
