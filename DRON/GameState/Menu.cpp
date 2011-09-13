/**
 *  GameState/Menu.cpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#include "Menu.hpp"

//#include <WinUser.h>

#include "../Display/D3D11Renderer.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/ComponentTypes.hpp"

Menu::Menu( EntitySystem& es, D3D11Renderer& r )
	: _entity_system( es ), _renderer( r ), _camera( es.CreateNewEntity() )
{
	es.AttachComponent( _camera, COMPONENT_CAMERA );
	es.AttachComponent( _camera, COMPONENT_MOVABLE );
	es.AttachComponent( _camera, COMPONENT_XFORM );

	_mapped_actions.insert( ActionMapPair( VK_RETURN, ACTION_SELECT ) );
	_mapped_actions.insert( ActionMapPair( VK_UP, ACTION_MOVE_UP ) );
	_mapped_actions.insert( ActionMapPair( VK_DOWN, ACTION_MOVE_DOWN ) );
	_mapped_actions.insert( ActionMapPair( VK_ESCAPE, ACTION_EXIT ) );
	
}

void Menu::Update( float dt )
{
	ProcessInput();
	_renderer.Draw();
}

void Menu::HandleKeypress( const WPARAM key )
{
	ACTION action;
	if( MapKeyToAction( key, action ) )
		_actions.push_back( action );
}

void Menu::ProcessInput()
{
	ActionDeque::const_iterator iter = _actions.begin();
	if( iter == _actions.end() )
		return;

	ACTION action = *iter;

	switch( action )
	{
		case ACTION_MOVE_UP:
			break;

		case ACTION_MOVE_DOWN:
			break;

		case ACTION_SELECT:
			break;

		case ACTION_EXIT:
			PostQuitMessage( 0 );
			break;

		default:
			break;
	}
	_actions.pop_front();
}