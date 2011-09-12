/**
 *  GameState/Menu.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef _MENU_HPP_
#define _MENU_HPP_

#include "GameState.hpp"

typedef unsigned int Entity;
class EntitySystem;
class D3D11Renderer;
class Menu : public GameState
{
	public:
		Menu( EntitySystem&, D3D11Renderer& );
		virtual ~Menu() { }

		void Update( float );

	private:
		EntitySystem&	_entity_system;
		D3D11Renderer&	_renderer;
		Entity			_camera;
};

#endif  _MENU_HPP_
