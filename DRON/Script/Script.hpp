/**
 *  Script/Script.hpp
 *  (c) Jonathan Capps
 *  Created 28 Sept. 2011
 */

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

struct lua_State;
class Script
{
	public:
		Script();
		~Script();

	private:
		Script( const Script& );
		Script& operator=( const Script& );

		lua_State*	_ls_ptr;
};

#endif //SCRIPT_HPP
