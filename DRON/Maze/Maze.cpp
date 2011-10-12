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
#include "../Utility/Rotations.hpp"

const char maze_def[] =
	"..............A.A.............."
	".F-----------7I.IF-----------7."
	".IoooooooooooII.IIoooooooooooI."
	".IOF--7oF--7oII.IIoF--7oF--7OI."
	".IoI..IoI..IoII.IIoI..IoI..IoI."
	".IoL--JoL--JoLJ+LJoL--JoL--JoI."
	".IoooooooooooooooooooooooooooI."
	".IoF--7oF-7oF-----7oF-7oF--7oI."
	".IoI..IoI.IoL-7.F-JoI.IoI..IoI."
	".IoI..IoI.IoooI.IoooI.IoI..IoI."
	".IoL--JoI.L-7.I.I.F-J.IoL--JoI."
	".IooooooI.F-J.L-J.L-7.IooooooI."
	".L----7oI.I....1....I.IoF----J."
	"......IoI.I.F--=--7.I.IoI......"
	"<-----JoL-J.I2.3.4I.L-JoL----->"
	"......+o....L-----J....o+......"
	"<-----7oF-7.........F-7oF----->"
	"......IoI.I.F-----7.I.IoI......"
	".F----JoL-J.L-7.F-J.L-JoL----7."
	".IooooooooooooI.IooooooooooooI."
	".IoF--7oF---7oI.IoF---7oF--7oI."
	".IoL-7IoL---JoL-JoL---JoIF-JoI."
	".IOooIIooooooooCooooooooIIooOI."
	".L-7oIIoF-7oF-----7oF-7oIIoF-J."
	".F-JoLJoI.IoL-7.F-JoI.IoLJoL-7."
	".IooooooI.IoooI.IoooI.IooooooI."
	".IoF----J.L-7oI.IoF-J.L----7oI."
	".IoL--------JoL-JoL--------JoI."
	".IoooooooooooooooooooooooooooI."
	".L------------7+F------------J."
	"..............V.V..............";

std::string maze_definition( maze_def );

Maze::Maze( const std::string& filename, EntitySystem& es )
	: _entity_system( es )
{
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
