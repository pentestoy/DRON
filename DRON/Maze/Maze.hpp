/**
 *  Maze/Maze.hpp
 *  (c) Jonathan Capps
 *  Created 24 Sept. 2011
 */

#ifndef MAZE_MAZE_HPP
#define MAZE_MAZE_HPP

#include <string>
#include <vector>
#include <D3D11.h>
#include "../Entity/Entity.hpp"
#include "../Utility/AlignedPtr.hpp"

class EntitySystem;
class MazeSide;
class Maze
{
	public:
		Maze( const std::string& filename, EntitySystem& es );
		
		void GetRenderableEntities( std::vector< Entity >& entities );

	private:
		Maze( const Maze& );
		Maze& operator=( const Maze& );

		void BuildMazeMesh();

		std::vector< MazeSide* > _sides;
		EntitySystem&			 _entity_system;
		ID3D11Buffer*			 _maze_vb;
		ID3D11Buffer*			 _maze_ib;
};

#endif //MAZE_MAZE_HPP
