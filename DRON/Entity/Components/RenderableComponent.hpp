/**
 *  Entity/Components/RenderableComponent.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef RENDERABLE_COMPONENT_HPP
#define RENDERABLE_COMPONENT_HPP

#include "BaseComponent.hpp"
#include <string>
#include <xnamath.h>

class RenderableComponent : public TplComponent< RenderableComponent >
{
	public:
		struct Data : public BaseComponent::Data
		{
			std::string _mesh_name;
			std::string _vertex_shader_filename;
			std::string _vertex_shader;
			std::string _pixel_shader_filename;
			std::string _pixel_shader;
			XMFLOAT4	_color;
		};
		Data& GetData() { return _data; }
		virtual void SetData( BaseComponent::Data& data )
			{ _data	= static_cast< Data& >( data ); }

	private:
		Data	_data;
};

COMPONENT_TYPE TplComponent< RenderableComponent >::_type = COMPONENT_RENDERABLE;
AutoRegistrar< RenderableComponent > TplComponent< RenderableComponent >::_registrar;

#endif  //RENDERABLE_COMPONENT_HPP
