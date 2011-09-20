/**
 *  Resource/MeshLocator.hpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#ifndef MESH_LOCATOR_HPP
#define MESH_LOCATOR_HPP

#include <string>
#include "MeshResource.hpp"

struct ID3D11Device;
class MeshCache;
class MeshLocator
{
	public:
		MeshLocator( ID3D11Device* device );
		MeshResource& Request( const std::string& filename );

	private:
		static MeshCache	_cache;
};

#endif //MESH_LOCATOR_HPP
