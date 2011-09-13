/**
 *  GameState/Menu.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "GameState.hpp"
#include <deque>

typedef unsigned int Entity;
class EntitySystem;
class D3D11Renderer;
class Menu : public GameState
{
	public:
		Menu( EntitySystem& es, D3D11Renderer& r );
		virtual ~Menu() { }

		virtual void Update( float dt );
		virtual void HandleKeypress( const WPARAM key );

	private:
		void ProcessInput();

		EntitySystem&	_entity_system;
		D3D11Renderer&	_renderer;
		Entity			_camera;

		typedef std::deque< ACTION > ActionDeque;
		ActionDeque	_actions;
};

#endif  _MENU_HPP_
