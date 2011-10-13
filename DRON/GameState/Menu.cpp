/**
 *  GameState/Menu.cpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#include "Menu.hpp"

#include "../Display/D3D11Renderer.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/ComponentTypes.hpp"
#include "../Entity/Components/Components.hpp"
#include "../Maze/Maze.hpp"

Menu::Menu( EntitySystem& es, D3D11Renderer& r )
	: _entity_system( es ), _renderer( r ),
	  _theta( 0 ), _phi( 0 ), _direction( ACTION_MOVE_STOP ),
	  _camera( _entity_system.CreateNewEntity() ),
	  _maze( new Maze( "Maze01.lua", es ) )
{
	XMVECTOR player_start = XMVectorSet( 0.0f, -7.0f, -15.0f, 0.0f );
	player_start = XMVector3Normalize( player_start );
	player_start *= 42.0f;

	CameraComponent::Data cd;
	cd._position = player_start;
	cd._lookat   = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
	cd._up       = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( _camera, COMPONENT_CAMERA, cd );

	MovableComponent::Data md;
	_entity_system.CreateAndAttachComponent( _camera, COMPONENT_MOVABLE, md );

	XformComponent::Data xd;
	_entity_system.CreateAndAttachComponent( _camera, COMPONENT_XFORM, xd );

	_mapped_actions.insert( ActionMapPair( VK_RETURN, ACTION_SELECT ) );
	_mapped_actions.insert( ActionMapPair( VK_UP, ACTION_MOVE_UP ) );
	_mapped_actions.insert( ActionMapPair( VK_DOWN, ACTION_MOVE_DOWN ) );

	_mapped_actions.insert( ActionMapPair( VK_LEFT, ACTION_MOVE_LEFT ) );
	_mapped_actions.insert( ActionMapPair( VK_RIGHT, ACTION_MOVE_RIGHT ) );

	_mapped_actions.insert( ActionMapPair( VK_ESCAPE, ACTION_EXIT ) );
}

void Menu::Update( float dt )
{
	ProcessInput();

	if( _direction == ACTION_MOVE_UP )
		_phi += ( XM_PIDIV2 * dt ) / 5.0f;

	else if( _direction == ACTION_MOVE_DOWN )
		_phi -= ( XM_PIDIV2 * dt ) / 5.0f;

	else if( _direction == ACTION_MOVE_RIGHT )
		_theta += ( XM_PIDIV2 * dt ) / 5.0f;

	else if( _direction == ACTION_MOVE_LEFT )
		_theta -= ( XM_PIDIV2 * dt ) / 5.0f;

	const CameraComponent::Data& camera_data =
		static_cast< const CameraComponent::Data& >( _entity_system.GetComponentData( _camera, COMPONENT_CAMERA ) );
	XMVECTOR old_position = camera_data._position;
	XMVECTOR length = XMVector3Length( old_position );
	
	float distance = XMVectorGetX( length ); 
	float x_equator = sin( _theta );
	float z_equator = cos( _theta + XM_PI );

	float azimuth   = sin( _phi );
	float scale     = cos( _phi );
	float x = x_equator * scale;
	float z = z_equator * scale;
	float y = azimuth;

	CameraComponent::Data new_data = camera_data;
	new_data._position = XMVectorSet( x, y, z, 0.0f ) * distance;

	_entity_system.SetComponentData( _camera, COMPONENT_CAMERA, new_data );

	std::vector< Entity > entities;
	_maze->GetRenderableEntities( entities );
	_renderer.Draw( entities, _camera );
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
		case ACTION_MOVE_DOWN:
		case ACTION_MOVE_LEFT:
		case ACTION_MOVE_RIGHT:
			_direction = action;
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
