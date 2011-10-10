/**
 *  Resource/InputLayoutResource.cpp
 *  (c) Jonathan Capps
 *  Created 10 Oct. 2011
 */

#include "InputLayoutResource.hpp"
#include "../Display/D3D11/GFXDevice.hpp"
#include "../Utility/DXUtil.hpp"

InputLayoutResource::InputLayoutResource()
	: Resource()
{ }

InputLayoutResource::InputLayoutResource(
	GFXDevice& device,
	std::vector< D3D11_INPUT_ELEMENT_DESC >& descriptions,
	ID3DBlob* const blob )
{
	HR( device.GetRawDevicePtr()->CreateInputLayout(
		&descriptions[ 0 ],
		descriptions.size(),
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&_data ) );
}

InputLayoutResource::~InputLayoutResource()
{
	DXRelease( _data );
}
