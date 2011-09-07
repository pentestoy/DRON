/**
 *  Display/DisplaySettings.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _DISPLAY_SETTINGS_HPP_
#define _DISPLAY_SETTINGS_HPP_

struct DisplaySettings
{
    DisplaySettings();	// provide safe and sane defaults
    unsigned int _width;
    unsigned int _height;
    bool         _fullscreen;
};

#endif  _DISPLAY_SETTINGS_HPP_
