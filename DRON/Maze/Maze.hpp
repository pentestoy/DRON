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
		std::vector< Entity > _walls;

};

class Maze
{
	public:
		Maze() {}

	private:
		std::vector< MazeSide* > _sides;

};

#endif //MAZE_HPP
