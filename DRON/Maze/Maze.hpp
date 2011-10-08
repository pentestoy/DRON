/**
 *  Maze/Maze.hpp
 *  (c) Jonathan Capps
 *  Created 24 Sept. 2011
 */

#ifndef MAZE_HPP
#define MAZE_HPP

#include <vector>
#include "../Entity/Entity.hpp"

class MazeSide
{
	public:
		MazeSide() {}

	private:
		MazeSide( const MazeSide& );
		MazeSide& operator=( const MazeSide& );

		std::vector< Entity > _walls;

};

class Maze
{
	public:
		Maze() {}

	private:
		Maze( const Maze& );
		Maze& operator=( const Maze& );

		std::vector< MazeSide* > _sides;

};

#endif //MAZE_HPP
