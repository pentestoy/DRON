/**
 *  Entity/Components/RenderableComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef RENDERABLE_COMPONENT_HPP
#define RENDERABLE_COMPONENT_HPP

#include "BaseComponent.hpp"
#include <string>

class RenderableComponent : public TplComponent< RenderableComponent >
{
	public:
		struct Data : public BaseComponent::BaseComponentData
		{
			std::string _mesh_name;
		};
		virtual BaseComponent::BaseComponentData& GetData() { return _data; }
		virtual void SetData( BaseComponent::BaseComponentData& data )
			{ _data	= static_cast< Data& >( data ); }

	private:
		Data	_data;
};

COMPONENT_TYPE TplComponent< RenderableComponent >::_type = COMPONENT_RENDERABLE;
AutoRegistrar< RenderableComponent > TplComponent< RenderableComponent >::_registrar;

#endif  //RENDERABLE_COMPONENT_HPP
