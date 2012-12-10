/**
 *  Maze/Maze.hpp
 *  (c) Jonathan Capps
 *  Created 10 Oct. 2011
 */

#include "Maze.hpp"
#include <algorithm>
#include <string>
#include <Windows.h>
#include <xnamath.h>
#include "MazeSide.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/RenderableComponent.hpp"
#include "../Entity/Components/XformComponent.hpp"
#include "../Resource/MeshLocator.hpp"
#include "../Script/Script.hpp"
#include "../Utility/Geometry.hpp"
#include "../Utility/Rotations.hpp"

Maze::Maze( Script& s, const std::string& filename, EntitySystem& es )
	: _script( s ), _entity_system( es )
{
	_script.DoFile( filename );
	int num_sides = _script.GetNumber( "maze['number_of_sides']" );
	std::string maze_definition( _script.GetString( "maze['sides'][1]['data']" ) );

	XMVECTOR position = XMVectorSet( 0.0f, 0.0f, -15.0f, 0.0f );
	XMVECTOR rotation = IDENTITY_QUAT;
	MazeSide* ms = new MazeSide( 31, maze_definition, position, rotation, es );
	_sides.push_back( ms );

	XMVECTOR axis = XMVectorSet( 1.0f, 0.0f, 0.0f, 0.0f );
	rotation = XMQuaternionRotationAxis( axis, -XM_PIDIV2 );
	ms = new MazeSide( 31, maze_definition, position, rotation, es );
	_sides.push_back( ms );

	rotation = XMQuaternionRotationRollPitchYaw( -XM_PIDIV2, 0.0f, XM_PIDIV2 );
	ms = new MazeSide( 31, maze_definition, position, rotation, es );
	_sides.push_back( ms );

	rotation = XMQuaternionRotationRollPitchYaw( XM_PI, 0.0f, XM_PIDIV2 );
	ms = new MazeSide( 31, maze_definition, position, rotation, es );
	_sides.push_back( ms );

	rotation = XMQuaternionRotationRollPitchYaw( 0.0f, -XM_PIDIV2, -XM_PIDIV2 );
	ms = new MazeSide( 31, maze_definition, position, rotation, es );
	_sides.push_back( ms );

	rotation = XMQuaternionRotationRollPitchYaw( 0.0f, -XM_PIDIV2, 0.0f );
	ms = new MazeSide( 31, maze_definition, position, rotation, es );
	_sides.push_back( ms );
}

void Maze::GetRenderableEntities( std::vector< Entity >& entities )
{
	for( unsigned int count = 0; count < _sides.size(); ++count )
		entities.insert( entities.begin(), _sides[ count ]->_walls.begin(), _sides[ count ]->_walls.end() );
}
