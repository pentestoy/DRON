/**
 *  Entity/Components/MovableComponent.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef MOVALBE_COMPONENT_HPP
#define MOVALBE_COMPONENT_HPP

#include "BaseComponent.hpp"

class MovableComponent : public TplComponent< MovableComponent >
{
	public:
		struct Data : public BaseComponentData
		{ };
		Data& GetData() { return _data; }
		void SetData( BaseComponent::BaseComponentData& data )
			{ _data = static_cast< Data& >( data ); }

	private:
		Data	_data;
};

COMPONENT_TYPE TplComponent< MovableComponent >::_type = COMPONENT_MOVABLE;
AutoRegistrar< MovableComponent > TplComponent< MovableComponent >::_registrar;

#endif  //MOVALBE_COMPONENT_HPP
