/**
 *  Display/D3D11/RenderTarget.hpp
 *  (c) Jonathan Capps
 *  Created 30 Sept. 2011
 */

#include "RenderTarget.hpp"
#include "../../Utility/DXUtil.hpp"

RenderTarget::RenderTarget()
	: _data( 0 )
{ }

RenderTarget::~RenderTarget()
{
	DXRelease( _data );
}

ID3D11RenderTargetView* RenderTarget::GetData()
{
	return _data;
}

ID3D11RenderTargetView** RenderTarget::GetDataAddress()
{
	return &_data;
}

void RenderTarget::ReleaseData()
{
	DXRelease( _data );
}
