/**
 *  Resource/PixelShaderResource.cpp
 *  (c) Jonathan Capps
 *  Created 16 Sept. 2011
 */

#include "PixelShaderResource.hpp"
#include "../Utility/DXUtil.hpp"

PixelShaderResource::~PixelShaderResource()
{
	/* SOMEHOW this is getting released according to the dxdebug :? */
	//DXRelease( _data );
	//if( _data )
	//	_data->Release();
}
