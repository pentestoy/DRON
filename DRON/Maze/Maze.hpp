/**
 *  Maze/Maze.hpp
 *  (c) Jonathan Capps
 *  Created 24 Sept. 2011
 */

#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

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
		MazeSide();

	private:
		MazeSide( const MazeSide& );
		MazeSide& operator=( const MazeSide& );

		friend class Maze;

		std::vector< Entity >  _walls;
		std::string            _maze_data;
		unsigned int		   _maze_size;
		AlignedPtr< XMVECTOR > _position;
};

class EntitySystem;
class Maze
{
	public:
		Maze( const std::string& filename, EntitySystem& es );
		
		void GetRenderableEntities( std::vector< Entity >& entities );

	private:
		Maze( const Maze& );
		Maze& operator=( const Maze& );

		void GenerateMaze();

		std::vector< MazeSide* > _sides;
		EntitySystem&			 _entity_system;
};

#endif //MAZE_MAZE_HPP
