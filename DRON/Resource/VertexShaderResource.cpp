/**
 *  Resource/VertexShaderResource.cpp
 *  (c) Jonathan Capps
 *  Created 15 Sept. 2011
 */

#include "VertexShaderResource.hpp"
#include "../Utility/DXUtil.hpp"

VertexShaderResource::~VertexShaderResource()
{
	DXRelease( _data );
}
