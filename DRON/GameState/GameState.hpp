/**
 *  GameState/GameState.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <map>
#include <string>
#include <Windows.h>
#include "../Input/ActionConstants.hpp"

class GameState
{
	public:
		GameState() { }
		virtual ~GameState() { }
		virtual void Update( float dt ) = 0;
		virtual void HandleKeypress( const WPARAM key ) = 0;

	protected:
		bool MapKeyToAction( const WPARAM key, ACTION& action );

		typedef std::map< WPARAM, ACTION > ActionMap;
		typedef std::pair< WPARAM, ACTION > ActionMapPair;
		ActionMap	_mapped_actions;
};

#endif  GAME_STATE_HPP
