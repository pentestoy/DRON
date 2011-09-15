/**
 *  Resource/MeshManager.hpp
 *  (c) Jonathan Capps
 *  Created 11 Sept. 2011
 */

#ifndef MESH_MANAGER_HPP
#define MESH_MANAGER_HPP

#include "ResourceManager.hpp"

#include <string>

class Mesh
{ };

class MeshManager;
class MeshResource : public Resource< Mesh >
{
	public:
		friend MeshManager;
};

class MeshManager : public ResourceManager< MeshResource >
{
	public:
		MeshManager() {}
		~MeshManager() {}

		virtual unsigned int LoadResource( const std::string& filename );

	private:
		Mesh* LoadMesh( const std::string& filename ); 
};

#endif //MESH_MANAGER_HPP
