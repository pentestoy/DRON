/**
 *  GameState/GameState.cpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#include "GameState.hpp"

bool GameState::MapKeyToAction( const WPARAM key, ACTION& action )
{
	ActionMap::const_iterator iter = _mapped_actions.find( key );
	if( iter == _mapped_actions.end() )
		return false;

	action = ( *iter ).second;
	return true;
}