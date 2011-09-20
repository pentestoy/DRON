/**
 *  Resource/MeshResource.cpp
 *  (c) Jonathan Capps
 *  Created 19 Sept. 2011
 */

#include "MeshResource.hpp"
#include "../Utility/Geometry.hpp"

MeshResource::~MeshResource()
{
	delete _data;
	_data = 0;
}
