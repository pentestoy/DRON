/**
 *  Script/Script.cpp
 *  (c) Jonathan Capps
 *  Created 28 Sept. 2011
 */

#include "Script.hpp"
#include "Lua.hpp"
#include <lua_icxx.h>
#include <LuaTempResult.h>

void Script::LuaStateDeleter::operator()( lua_State* lua_state_ptr ) const
{
	lua_close( lua_state_ptr );
}

Script::Script( const std::string& path )
	: _path( path ), _ls_ptr( luaL_newstate() ),
	  _interpreter_ptr( new LuaInterpreter( _ls_ptr.get() ) )
{ }

Script::~Script()
{ }

bool Script::DoFile( const std::string& filename )
{
	std::string path_and_filename = _path + filename;
	LuaTempResult ltr = _interpreter_ptr->doFile( path_and_filename );
	if( ltr.ok() )
	{
		return true;
	}

	return false;
}

std::string Script::GetString( const std::string& variable ) const
{
	LuaTempResult ltr = _interpreter_ptr->eval( variable );
	return std::string( static_cast< std::string >( ltr ) );
}

int Script::GetNumber( const std::string& variable ) const
{
	LuaTempResult ltr = _interpreter_ptr->eval( variable );
	return int( static_cast< int >( ltr ) );
}
