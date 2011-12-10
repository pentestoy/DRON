/**
 *  GameState/Menu.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef MENU_HPP
#define MENU_HPP

#include "GameState.hpp"
#include <deque>
#include <vector>
#include "../Entity/Entity.hpp"

class EntitySystem;
class D3D11Renderer;
class Maze;
class Script;
class Menu : public GameState
{
	public:
		Menu( EntitySystem& es, D3D11Renderer& r, Script& s );
		virtual ~Menu() { }

		virtual void Update( float dt );
		virtual void HandleKeypress( const WPARAM key );

	private:
		Menu( const Menu& );
		Menu& operator=( const Menu& );

		void ProcessInput();

		EntitySystem&	_entity_system;
		D3D11Renderer&	_renderer;
		Script&			_script;

		Entity			_camera;

		Maze*			_maze;

		float	_theta; //0 is -Z axis, increases ccw looking down the +Y axis.
		float	_phi;   //0 is XZ plane increases going up and around.
		ACTION  _direction;

		typedef std::deque< ACTION > ActionDeque;
		ActionDeque	_actions;
};

#endif  MENU_HPP
