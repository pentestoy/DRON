/**
 *  Display/DisplaySettings.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _DISPLAY_SETTINGS_HPP_
#define _DISPLAY_SETTINGS_HPP_

struct DisplaySettings
{
    DisplaySettings()
		: _width(800), _height(600), _fullscreen(false) { }

    unsigned int _width;
    unsigned int _height;
    bool         _fullscreen;
};

#endif  //_DISPLAY_SETTINGS_HPP_
