/**
 *  Maze/MazeSide.hpp
 *  (c) Jonathan Capps
 *  Created 11 Oct. 2011
 */

#ifndef MAZE_MAZE_SIDE_HPP
#define MAZE_MAZE_SIDE_HPP

#include <string>
#include <vector>
#include <Windows.h>
#include <xnamath.h>
#include "../Entity/Entity.hpp"
#include "../Utility/AlignedPtr.hpp"

class EntitySystem;
class Maze;
class MazeSide
{
	public:
		MazeSide();
		MazeSide(
			unsigned int size,
			std::string& definition,
			XMVECTOR& position,
			XMVECTOR& rotation,
			EntitySystem& es );

		void SetPosition( XMVECTOR& position );
		void SetPosition( float x, float y, float z );
		XMVECTOR& GetPosition() const;

		void SetRotation( XMVECTOR& rotation );
		void SetRotation( float x, float y, float z, float w );
		XMVECTOR& GetRotation() const;

		void SetMazeSize( unsigned int size );
		void SetMazeDefinition( const std::string& definition );

		void ProcessMaze( EntitySystem& es );

	private:
		MazeSide( const MazeSide& );
		MazeSide& operator=( const MazeSide& );

		friend class Maze;

		std::vector< Entity >  _walls;
		std::string            _maze_data;
		unsigned int		   _size;
		AlignedPtr< XMVECTOR > _position;
		AlignedPtr< XMVECTOR > _rotation;
};

#endif //MAZE_MAZE_SIDE_HPP
