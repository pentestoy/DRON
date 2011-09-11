/**
 *  Entity/Components/XformComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _XFORM_COMPONENT_HPP_
#define _XFORM_COMPONENT_HPP_

#include "BaseComponent.hpp"
#include <Windows.h>
#include <xnamath.h>

struct XformData
{
	XMFLOAT4	_position;
	XMFLOAT4	_scale;
	XMFLOAT4	_rotation;
};

class XformComponent : public TplComponent< XformComponent >
{
	public:
		XformData& Data() { return _data; }

	private:
		XformData	_data;
};

COMPONENT_TYPE TplComponent< XformComponent >::_type = COMPONENT_XFORM;
AutoRegistrar< XformComponent > TplComponent< XformComponent >::_registrar;

#endif  //_XFORM_COMPONENT_HPP_