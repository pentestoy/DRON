/**
 *  Entity/Components/RenderableComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef RENDERABLE_COMPONENT_HPP
#define RENDERABLE_COMPONENT_HPP

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
		void SetMeshName( const std::string& name ) { _data._mesh_name = name; }

	private:
		RenderableData	_data;
};

COMPONENT_TYPE TplComponent< RenderableComponent >::_type = COMPONENT_RENDERABLE;
AutoRegistrar< RenderableComponent > TplComponent< RenderableComponent >::_registrar;

#endif  //RENDERABLE_COMPONENT_HPP
