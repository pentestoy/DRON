/**
 *  Resource/MeshResource.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef MESH_RESOURCE_HPP
#define MESH_RESOURCE_HPP

#include "BaseResource.hpp"

struct aiMesh;
class MeshCache;
class MeshResource : public Resource< aiMesh >
{
	public:
		~MeshResource();
		aiMesh* Data() { return _data; }

		friend MeshCache;
};

#endif //MESH_RESOURCE_HPP
