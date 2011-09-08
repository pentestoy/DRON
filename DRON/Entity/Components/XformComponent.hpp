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
	XMVECTOR	_position;
	XMVECTOR	_scale;
	XMVECTOR	_rotation;
};

class XformComponent : public TplComponent< XformComponent >
{
	public:
		typedef XformData ComponentData;
		XformData GetData() const { return _data; }

	private:
		XformData	_data;
};

COMPONENT_TYPE TplComponent< XformComponent >::_type = COMPONENT_XFORM;

#endif  _XFORM_COMPONENT_HPP_