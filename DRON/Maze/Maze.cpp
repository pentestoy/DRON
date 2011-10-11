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

const XMVECTOR QUARTER_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	XM_PIDIV2 );

const XMVECTOR HALF_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	XM_PI );

const XMVECTOR THREE_QUARTER_TURN = XMQuaternionRotationAxis(
	XMVectorSet( 0.0f, 0.0f, -1.0f, 0.0f ),
	3.0f * XM_PIDIV2 );

const XMVECTOR TOP_JOIN = XMQuaternionRotationRollPitchYaw(
	0.0f, -XM_PIDIV2, 0.0f );

const XMVECTOR SIDE_JOIN = XMQuaternionRotationRollPitchYaw(
	-XM_PIDIV2, -XM_PIDIV2, 0.0f );

Maze::Maze( const std::string& filename, EntitySystem& es )
	: _entity_system( es )
{
	GenerateMaze();
}

void Maze::GenerateMaze()
{
	/*****************************************************************************
	 * TODO: I still need to get the entity position transformed correctly
	 *       from the MazeSide's rotation;
	 */
	unsigned int maze_size = 31;
	XMVECTOR side_position = XMVectorSet( 0.0f, 0.0f, -15.0f, 1.0f );
	XMVECTOR axis = XMVectorSet( 1.0f, 0.0f, 0.0f, 0.0f );
	XMVECTOR side_rotation = XMQuaternionRotationAxis( axis, XM_PIDIV2 );//XMQuaternionIdentity();
	MazeSide* ms = new MazeSide(
		maze_size,
		maze_definition,
		side_position,
		side_rotation );
	
	for( unsigned int y_index = 0; y_index < maze_size; ++y_index )
	{
		for( unsigned int x_index = 0; x_index < maze_size; ++x_index )
		{
			char c = maze_definition[ y_index * 31 + x_index ];

			float x_offset = (float)x_index - 15.0f;
			float y_offset = 15.0f - (float)y_index;
			XMVECTOR wall_color = XMVectorSet( 0.2f, 0.3f, 1.0f, 1.0f );
			switch( c )
			{
				case 'F':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( XMQuaternionIdentity(), ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case '7':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( QUARTER_TURN, ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case 'J':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( HALF_TURN, ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case 'L':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( THREE_QUARTER_TURN, ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case 'A':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( TOP_JOIN, ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case '>':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( SIDE_JOIN, ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case '-':
				{
					/* We ignore it if it's not the first of a sequence */
					if( maze_definition[ y_index * 31 + x_index - 1 ] == '-' )
						break;

					unsigned int count = 1;
					while( maze_definition[ y_index * 31 + x_index + count ] == '-' )
						++count;

					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset + ( ( float ) count - 1.0f )/ 2.0f, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( XMQuaternionIdentity(), ms->GetRotation() );
					xd._scale    = XMVectorSet( ( float )count, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe00.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}

				case 'I':
				{
					/* We ignore it if it's not the first of a sequence */
					if( maze_definition[ ( y_index - 1 ) * 31 + x_index ] == 'I' )
						break;

					unsigned int count = 1;
					while( maze_definition[ ( y_index + count ) * 31 + x_index ] == 'I' )
						++count;

					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset - ( ( float )count - 1.0f ) / 2.0f, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( QUARTER_TURN, ms->GetRotation() );
					xd._scale    = XMVectorSet( ( float )count, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe00.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}
				case '=':
				{
					Entity e = _entity_system.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = ms->GetPosition() + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._rotation = XMQuaternionMultiply( XMQuaternionIdentity(), ms->GetRotation() );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe00.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = XMVectorSet( 1.0f, 0.9f, 0.9f, 1.0f );
					_entity_system.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					ms->_walls.push_back( e );
					break;
				}
			}
		}
	}

	_sides.push_back( ms );
}

void Maze::GetRenderableEntities( std::vector< Entity >& entities )
{
	entities.resize( _sides[ 0 ]->_walls.size() );
	std::copy( _sides[ 0 ]->_walls.begin(), _sides[ 0 ]->_walls.end(), entities.begin() );
}
