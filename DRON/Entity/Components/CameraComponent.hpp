/**
 *  Entity/Components/CameraComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef CAMERA_COMPONENT_HPP
#define CAMERA_COMPONENT_HPP

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
		struct Data : public BaseComponentData
		{
			XMVECTOR _lookat;
			XMVECTOR _up;
			Entity	 _tracked_target;
		};
		Data& GetData() { return _data; }
		void SetData( BaseComponent::BaseComponentData& data )
			{ _data = static_cast< Data& >( data ); }

	private:
		Data	_data;
};

COMPONENT_TYPE TplComponent< CameraComponent >::_type = COMPONENT_CAMERA;
AutoRegistrar< CameraComponent > TplComponent< CameraComponent >::_registrar;

#endif  //CAMERA_COMPONENT_HPP
