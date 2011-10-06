/**
 *  Entity/Components/XformComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef XFORM_COMPONENT_HPP
#define XFORM_COMPONENT_HPP

#include "BaseComponent.hpp"
#include <Windows.h>
#include <xnamath.h>

class XformComponent : public TplComponent< XformComponent >
{
	public:
		struct Data : public BaseComponent::Data
		{
			XMVECTOR	_position;
			XMVECTOR	_scale;
			XMVECTOR	_rotation;
		};
		Data& GetData() { return _data; }
		void SetData( BaseComponent::Data& data )
			{ _data = static_cast< Data& >( data ); }

	private:
		Data	_data;
};

COMPONENT_TYPE TplComponent< XformComponent >::_type = COMPONENT_XFORM;
AutoRegistrar< XformComponent > TplComponent< XformComponent >::_registrar;

#endif  //XFORM_COMPONENT_HPP
