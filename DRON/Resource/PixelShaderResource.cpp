/**
 *  Resource/PixelShaderResource.cpp
 *  (c) Jonathan Capps
 *  Created 16 Sept. 2011
 */

#include "PixelShaderResource.hpp"
#include "../Utility/DXUtil.hpp"

PixelShaderResource::~PixelShaderResource()
{
	DXRelease( _data );
}
