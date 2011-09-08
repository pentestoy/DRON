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
class Menu : public GameState
{
	public:
		Menu( EntitySystem& );
		virtual ~Menu() { }

		void Update( float );

	private:
		Entity	_camera;
};

#endif  _MENU_HPP_
