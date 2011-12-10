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

class CameraComponent : public TplComponent< CameraComponent >
{
	public:
		struct Data : public BaseComponent::Data
		{
			XMVECTOR _position;
			XMVECTOR _lookat;
			XMVECTOR _up;
			Entity	 _tracked_target;
		};
		Data& GetData() { return _data; }
		void SetData( BaseComponent::Data& data )
			{ _data = static_cast< Data& >( data ); }

	private:
		Data	_data;
};

COMPONENT_TYPE TplComponent< CameraComponent >::_type = COMPONENT_CAMERA;

#endif  //CAMERA_COMPONENT_HPP
