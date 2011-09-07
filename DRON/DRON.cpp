/**
 *  DRON.cpp
 *  This is the entry point for the program.
 *  (c) Jonathan Capps
 *  Created 06 Sept. 2011
 */

#include "targetver.h"
#include <Windows.h>
#include "App.hpp"

int WINAPI wWinMain( HINSTANCE instance, HINSTANCE prev_instance, LPTSTR cmd_line, int show )
{
	App app( instance );
	return app.Run();
}
