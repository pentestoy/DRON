/**
 *  Display/DisplaySettings.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef DISPLAY_SETTINGS_HPP
#define DISPLAY_SETTINGS_HPP

struct DisplaySettings
{
		DisplaySettings();
		DisplaySettings( const DisplaySettings& ds );
		DisplaySettings& operator=( const DisplaySettings& ds );

		unsigned int _width;
		unsigned int _height;
		bool         _fullscreen;
};

#endif  //DISPLAY_SETTINGS_HPP
