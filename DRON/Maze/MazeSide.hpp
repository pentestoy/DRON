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

class Maze;
class MazeSide
{
	public:
		MazeSide(
			unsigned int size,
			std::string& definition,
			XMVECTOR& position,
			XMVECTOR& rotation );

		XMVECTOR& GetPosition() const;
		XMVECTOR& GetRotation() const;
		void SetPosition( XMVECTOR& position );
		void SetRotation( XMVECTOR& rotation );

	private:
		MazeSide( const MazeSide& );
		MazeSide& operator=( const MazeSide& );

		friend class Maze;

		std::vector< Entity >  _walls;
		std::string            _maze_data;
		unsigned int		   _maze_size;
		AlignedPtr< XMVECTOR > _position;
		AlignedPtr< XMVECTOR > _rotation;
};

#endif //MAZE_MAZE_SIDE_HPP
