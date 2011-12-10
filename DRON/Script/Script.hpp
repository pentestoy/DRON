/**
 *  Script/Script.hpp
 *  (c) Jonathan Capps
 *  Created 28 Sept. 2011
 */

#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <memory>
#include <string>

struct lua_State;
class LuaInterpreter;
class Script
{
	public:
		Script( const std::string& path );
		~Script();

		bool DoFile( const std::string& filename );
		std::string GetString( const std::string& variable ) const;

	private:
		Script( const Script& );
		Script& operator=( const Script& );

		class LuaStateDeleter
		{
			public:
			void operator()(lua_State* lua_state_ptr ) const;
		};

		std::unique_ptr< lua_State, LuaStateDeleter >	_ls_ptr;
		std::unique_ptr< LuaInterpreter >				_interpreter_ptr;

		const std::string	_path;
};

#endif //SCRIPT_HPP
