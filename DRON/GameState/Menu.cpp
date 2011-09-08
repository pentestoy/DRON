/**
 *  GameState/Menu.cpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#include "Menu.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/ComponentTypes.hpp"

Menu::Menu( EntitySystem& es )
	: GameState( "Menu" ), _camera( es.CreateNewEntity() )
{
	es.AttachComponent( _camera, COMPONENT_CAMERA );
	es.AttachComponent( _camera, COMPONENT_MOVABLE );
	es.AttachComponent( _camera, COMPONENT_XFORM );
}

void Menu::Update( float dt )
{ }
