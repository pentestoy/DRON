%module Maze
%include "std_string.i"

%{
#include "../Entity/Entity.hpp"
#include "../Maze/MazeSide.hpp"
#include "../Maze/Maze.hpp"
%}

class Maze;
class MazeSide
{
	public:
		MazeSide();

		void SetPosition( float x, float y, float z );
		void SetRotation( float x, float y, float z, float w );
		void SetMazeSize( unsigned int size );
		void SetMazeDefinition( const std::string& definition );

	private:

		std::vector< Entity >  _walls;
		std::string            _maze_data;
		unsigned int		   _size;
		AlignedPtr< XMVECTOR > _position;
		AlignedPtr< XMVECTOR > _rotation;
};