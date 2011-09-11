/**
 *  Entity/Components/RenderableComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _RENDERABLE_COMPONENT_HPP_
#define _RENDERABLE_COMPONENT_HPP_

#include "BaseComponent.hpp"
#include <string>

struct RenderableData
{
	std::string _mesh_name;
};

class RenderableComponent : public TplComponent< RenderableComponent >
{
	public:
		typedef RenderableData ComponentData;
		RenderableData GetData() const { return _data; }

	private:
		RenderableData	_data;
};

COMPONENT_TYPE TplComponent< RenderableComponent >::_type = COMPONENT_RENDERABLE;
AutoRegistrar< RenderableComponent > TplComponent< RenderableComponent >::_registrar;

#endif  //_RENDERABLE_COMPONENT_HPP_
