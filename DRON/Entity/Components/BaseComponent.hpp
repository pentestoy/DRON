/**
 * Entity/BaseComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _BASE_COMPONENT_HPP_
#define _BASE_COMPONENT_HPP_

#include "ComponentTypes.hpp"

typedef unsigned int Entity;

class BaseComponent
{
	public:
		virtual COMPONENT_TYPE GetType() const = 0;
};

template< class T >
class TplComponent : public BaseComponent
{
	public:
		COMPONENT_TYPE GetType() const { return _type; }
	protected:
		static COMPONENT_TYPE _type;
};

#endif  _BASE_COMPONENT_HPP_
