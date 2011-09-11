/**
 *  Entity/Components/MovableComponent.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef _MOVALBE_COMPONENT_HPP_
#define _MOVALBE_COMPONENT_HPP_

#include "BaseComponent.hpp"

class MovableComponent : public TplComponent< MovableComponent >
{
	public:
		typedef int ComponentData;
		int GetData() const { return 0; }

	private:
		//int	_data;
};

COMPONENT_TYPE TplComponent< MovableComponent >::_type = COMPONENT_MOVABLE;
AutoRegistrar< MovableComponent > TplComponent< MovableComponent >::_registrar;

#endif  //_MOVALBE_COMPONENT_HPP_
