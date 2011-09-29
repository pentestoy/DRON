/**
 *  Script/Script.cpp
 *  (c) Jonathan Capps
 *  Created 28 Sept. 2011
 */

#include "Script.hpp"
#include "Lua.hpp"

Script::Script()
	: _ls_ptr( luaL_newstate() )
{ }

Script::~Script()
{
	lua_close( _ls_ptr );
}
