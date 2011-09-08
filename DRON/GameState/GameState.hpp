/**
 *  GameState/GameState.hpp
 *  (c) Jonathan Capps
 *  Created 08 Sept. 2011
 */

#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <string>

class GameState
{
	public:
		GameState( const std::string& );
		virtual ~GameState();
		const std::string& GetName() const { return _name; }
		virtual void Update( float ) = 0;

	protected:
		const std::string _name;
};

#endif  _GAME_STATE_HPP_
