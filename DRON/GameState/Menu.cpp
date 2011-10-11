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

const XMVECTOR QUARTER_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	XM_PIDIV2 );

const XMVECTOR HALF_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	XM_PI );

const XMVECTOR THREE_QUARTER_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	3.0f * XM_PIDIV2 );

Menu::Menu( EntitySystem& es, D3D11Renderer& r )
	: _entity_system( es ), _renderer( r ),
	  _camera( _entity_system.CreateNewEntity() ),
	  _maze( new Maze( "Maze01.lua", es ) )
{
	CameraComponent::Data cd;
	cd._position = XMVectorSet( 0.0f, 0.0f, -52.5f, 0.0f );
	cd._lookat   = XMVectorSet( 0.0f, 0.0f, 0.0f, 0.0f );
	cd._up       = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( _camera, COMPONENT_CAMERA, cd );

	MovableComponent::Data md;
	_entity_system.CreateAndAttachComponent( _camera, COMPONENT_MOVABLE, md );

	XformComponent::Data xd;
	_entity_system.CreateAndAttachComponent( _camera, COMPONENT_XFORM, xd );

	//CreateTestEntities();

	_mapped_actions.insert( ActionMapPair( VK_RETURN, ACTION_SELECT ) );
	_mapped_actions.insert( ActionMapPair( VK_UP, ACTION_MOVE_UP ) );
	_mapped_actions.insert( ActionMapPair( VK_DOWN, ACTION_MOVE_DOWN ) );
	_mapped_actions.insert( ActionMapPair( VK_ESCAPE, ACTION_EXIT ) );
}

void Menu::Update( float dt )
{
	ProcessInput();
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

/*
void Menu::CreateTestEntities()
{
	Entity e = _entity_system.CreateNewEntity();

	XformComponent::Data xd;
	xd._position = XMVectorSet( -2.0f, 1.0f, 0.0f, 1.0f );
	xd._rotation = XMQuaternionIdentity();
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

	RenderableComponent::Data rd;
	rd._mesh_name = "pipe90.x";
	rd._vertex_shader_filename = "test.fx";
	rd._vertex_shader = "VS_Test";
	rd._pixel_shader_filename = "test.fx";
	rd._pixel_shader = "PS_Test";
	rd._color = XMVectorSet( 0.5f, 0.5f, 1.0f, 1.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( 2.0f, 1.0f, 0.0f, 1.0f );
	xd._rotation = QUARTER_TURN;
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );
	
	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( 2.0f, -1.0f, 0.0f, 1.0f );
	xd._rotation = HALF_TURN;
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );
	
	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( -2.0f, -1.0f, 0.0f, 1.0f );
	xd._rotation = THREE_QUARTER_TURN;
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );
	
	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( 0.0f, 1.0f, 0.0f, 1.0f );
	xd._rotation = XMQuaternionIdentity();
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

	rd._mesh_name = "pipe00.x";
	rd._vertex_shader_filename = "test.fx";
	rd._vertex_shader = "VS_Test";
	rd._pixel_shader_filename = "test.fx";
	rd._pixel_shader = "PS_Test";
	rd._color = XMVectorSet( 1.0f, 0.9f, 0.9f, 1.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );
	
	/*
	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( -1.0f, 1.0f, 0.0f, 1.0f );
	xd._rotation = XMQuaternionIdentity();
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	rd._color = XMVectorSet( 0.5f, 0.5f, 1.0f, 1.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( 1.0f, 1.0f, 0.0f, 1.0f );
	xd._rotation = XMQuaternionIdentity();
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( 2.0f, 0.0f, 0.0f, 1.0f );
	xd._rotation = QUARTER_TURN;
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( 0.0f, -1.0f, 0.0f, 1.0f );
	xd._rotation = XMQuaternionIdentity();
	xd._scale    = XMVectorSet( 3.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );

	e = _entity_system.CreateNewEntity();

	xd._position = XMVectorSet( -2.0f, 0.0f, 0.0f, 1.0f );
	xd._rotation = QUARTER_TURN;
	xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );
	_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

	_entities.push_back( e );
	* /
}
*/
