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
class Menu : public GameState
{
	public:
		Menu( EntitySystem& es, D3D11Renderer& r );
		virtual ~Menu() { }

		virtual void Update( float dt );
		virtual void HandleKeypress( const WPARAM key );

	private:
		Menu& operator=( const Menu& );

		void CreateTestEntities();

		void ProcessInput();

		EntitySystem&	_entity_system;
		D3D11Renderer&	_renderer;
		Entity			_camera;
		//Entity			_test_entity;

		Maze*			_maze;

		typedef std::deque< ACTION > ActionDeque;
		ActionDeque	_actions;
		std::vector< Entity > _entities;
};

#endif  MENU_HPP
