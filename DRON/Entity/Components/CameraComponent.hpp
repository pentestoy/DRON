/**
 *  Entity/Components/CameraComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _CAMERA_COMPONENT_HPP_
#define _CAMERA_COMPONENT_HPP_

#include "BaseComponent.hpp"
#include <Windows.h>
#include <xnamath.h>

struct CameraData
{
	XMVECTOR _lookat;
	XMVECTOR _up;
	Entity	 _tracked_target;
};

class CameraComponent : public TplComponent< CameraComponent >
{
	public:
		typedef CameraData ComponentData;

		CameraData GetData() const { return _data; }

	private:
		CameraData	_data;
};

COMPONENT_TYPE TplComponent< CameraComponent >::_type = COMPONENT_CAMERA;

#endif  _CAMERA_COMPONENT_HPP_
