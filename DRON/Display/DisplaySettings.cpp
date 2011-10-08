/**
 *  Display/DisplaySettings.cpp
 *  (c) Jonathan Capps
 *  Created 08 Oct. 2011
 */

#include "DisplaySettings.hpp"

DisplaySettings::DisplaySettings()
	: _width( 800 ), _height( 600 ), _fullscreen( false )
{ }

DisplaySettings::DisplaySettings( const DisplaySettings& ds )
	: _width( ds._width ), _height( ds._height ), _fullscreen( ds._fullscreen )
{ }

DisplaySettings& DisplaySettings::operator=( const DisplaySettings& ds )
{
	_width = ds._width;
	_height = ds._height;
	_fullscreen = ds._fullscreen;

	return *this;
}