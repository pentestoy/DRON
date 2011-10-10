/**
 *  Resource/InputLayoutResource.hpp
 *  (c) Jonathan Capps
 *  Created 10 Oct. 2011
 */

#ifndef RESOURCE_INPUT_LAYOUT_RESOURCE_HPP
#define RESOURCE_INPUT_LAYOUT_RESOURCE_HPP

#include "BaseResource.hpp"
#include <vector>
#include <D3D11.h>

class GFXDevice;
class InputLayoutResource : public Resource< ID3D11InputLayout >
{
	public:
		InputLayoutResource();
		InputLayoutResource(
			GFXDevice& device,
			std::vector< D3D11_INPUT_ELEMENT_DESC >& descriptions,
			ID3DBlob* const blob );
		~InputLayoutResource();

		bool IsValid() { return _data != 0; }
};

#endif //RESOURCE_INPUT_LAYOUT_RESOURCE_HPP
