/**
 *  Resource/MeshCache.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef MESH_CACHE_HPP
#define MESH_CACHE_HPP

#include <map>
#include <string>

class MeshResource;
class MeshCache
{
	public:
		MeshCache();
		~MeshCache();

		MeshResource& Request( const std::string& filename );

	private:
		MeshResource& Load( const std::string& filename );

		typedef std::map< std::string, MeshResource* > ResourceMap;
		ResourceMap		_resources;
};

#endif //MESH_CACHE_HPP
