/**
 *  Maze/MazeSide.cpp
 *  (c) Jonathan Capps
 *  Created 11 Oct. 2011
 */

#include "MazeSide.hpp"
#include "../Entity/EntitySystem.hpp"
#include "../Entity/Components/RenderableComponent.hpp"
#include "../Entity/Components/XformComponent.hpp"
#include "../Utility/Rotations.hpp"

MazeSide::MazeSide()
	: _size( 0 ), _maze_data( "" )
{
	_position.Reset();
	_rotation.Reset();
}

MazeSide::MazeSide(
	unsigned int size,
	std::string& definition,
	XMVECTOR& position,
	XMVECTOR& rotation,
	EntitySystem& es )
	: _size( size ), _maze_data( definition )
{
	_position.Reset( position );
	_rotation.Reset( rotation );

	ProcessMaze( es );
}

XMVECTOR& MazeSide::GetPosition() const
{
	return *_position;
}

void MazeSide::SetPosition( XMVECTOR& position )
{
	_position.Reset( position );
}

void MazeSide::SetPosition( float x, float y, float z )
{
	_position.Reset( XMVectorSet( x, y, z, 0.0f ) );
}

XMVECTOR& MazeSide::GetRotation() const
{
	return *_rotation;
}

void MazeSide::SetRotation( XMVECTOR& rotation )
{
	_rotation.Reset( rotation );
}

void MazeSide::SetRotation( float x, float y, float z, float w )
{
	_rotation.Reset( XMVectorSet( x, y, z, w ) );
}

void MazeSide::SetMazeSize( unsigned int size )
{
	_size = size;
}

void MazeSide::SetMazeDefinition( const std::string& definition )
{
	_maze_data = definition;
}

void MazeSide::ProcessMaze( EntitySystem& es )
{
	XMVECTOR rotation_conj = XMQuaternionConjugate( *_rotation );

	for( unsigned int y_index = 0; y_index < _size; ++y_index )
	{
		for( unsigned int x_index = 0; x_index < _size; ++x_index )
		{
			char c = _maze_data[ y_index * 31 + x_index ];

			float x_offset = ( float )x_index - ( ( float )_size - 1.0f ) / 2.0f;
			float y_offset = ( ( float )_size - 1.0f ) / 2.0f - (float)y_index;
			XMVECTOR wall_color = XMVectorSet( 0.2f, 0.3f, 1.0f, 1.0f );
			switch( c )
			{
				case 'F':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( IDENTITY_QUAT, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case '7':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( QUARTER_TURN, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case 'J':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( HALF_TURN, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case 'L':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( THREE_QUARTER_TURN, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case 'A':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( TOP_JOIN, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case '>':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( SIDE_JOIN, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe90.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case '-':
				{
					/* We ignore it if it's not the first of a sequence */
					if( _maze_data[ y_index * 31 + x_index - 1 ] == '-' )
						break;

					unsigned int count = 1;
					while( _maze_data[ y_index * 31 + x_index + count ] == '-' )
						++count;

					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset + ( ( float ) count - 1.0f )/ 2.0f, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( IDENTITY_QUAT, rotation_conj );
					xd._scale    = XMVectorSet( ( float )count, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe00.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case 'I':
				{
					/* We ignore it if it's not the first of a sequence */
					if( _maze_data[ ( y_index - 1 ) * 31 + x_index ] == 'I' )
						break;

					unsigned int count = 1;
					while( _maze_data[ ( y_index + count ) * 31 + x_index ] == 'I' )
						++count;

					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset - ( ( float )count - 1.0f ) / 2.0f, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( QUARTER_TURN, rotation_conj );
					xd._scale    = XMVectorSet( ( float )count, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe00.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = wall_color;
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}

				case '=':
				{
					Entity e = es.CreateNewEntity();

					XformComponent::Data xd;
					xd._position = *_position + XMVectorSet( x_offset, y_offset, 0.0f, 1.0f );
					xd._position = XMQuaternionMultiply( *_rotation, xd._position );
					xd._position = XMQuaternionMultiply( xd._position, rotation_conj );
					xd._rotation = XMQuaternionMultiply( IDENTITY_QUAT, rotation_conj );
					xd._scale    = XMVectorSet( 1.0f, 1.0f, 1.0f, 0.0f );
					es.CreateAndAttachComponent( e, COMPONENT_XFORM, xd );

					RenderableComponent::Data rd;
					rd._mesh_name = "pipe00.x";
					rd._vertex_shader_filename = "test.fx";
					rd._vertex_shader = "VS_Test";
					rd._pixel_shader_filename = "test.fx";
					rd._pixel_shader = "PS_Test";
					rd._color = XMVectorSet( 1.0f, 0.9f, 0.9f, 1.0f );
					es.CreateAndAttachComponent( e, COMPONENT_RENDERABLE, rd );

					_walls.push_back( e );
					break;
				}
			}
		}
	}

	//_sides.push_back( ms );
}