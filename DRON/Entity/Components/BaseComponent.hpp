/**
 * Entity/BaseComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _BASE_COMPONENT_HPP_
#define _BASE_COMPONENT_HPP_

#include "ComponentTypes.hpp"
#include "../EntitySystem.hpp"

typedef unsigned int Entity;

class BaseComponent
{
	public:
		virtual COMPONENT_TYPE GetType() const = 0;
};

template< class T >
struct AutoRegistrar
{
	AutoRegistrar()
	{
		/*****************************************************
		 *
		 * TODO: Register the component with the EntitySystem.
		 *
		 *****************************************************/
	}
};

template< class T >
class TplComponent : public BaseComponent
{
	public:
		TplComponent() { &_registrar; }
		COMPONENT_TYPE GetType() const { return _type; }
		static COMPONENT_TYPE GetTypeStatic() { return _type; }
	protected:
		static COMPONENT_TYPE _type;
		static AutoRegistrar< T > _registrar;
};

template< class T > AutoRegistrar< T > TplComponent< T >::_registrar;

#endif  _BASE_COMPONENT_HPP_
