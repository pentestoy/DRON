/**
 *  Maze/MazeSide.cpp
 *  (c) Jonathan Capps
 *  Created 11 Oct. 2011
 */

#include "MazeSide.hpp"

MazeSide::MazeSide(
	unsigned int size,
	std::string& definition,
	XMVECTOR& position,
	XMVECTOR& rotation )
	: _maze_size( size ), _maze_data( definition )
{
	_position.Reset( position );
	_rotation.Reset( rotation );
}

XMVECTOR& MazeSide::GetPosition() const
{
	return *_position;
}

XMVECTOR& MazeSide::GetRotation() const
{
	return *_rotation;
}

void MazeSide::SetPosition( XMVECTOR& position )
{
	_position.Reset( position );
}

void MazeSide::SetRotation( XMVECTOR& rotation )
{
	_rotation.Reset( rotation );
}
