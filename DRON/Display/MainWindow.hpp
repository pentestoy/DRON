/**
 *  Display/MainWindow.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include "BaseWindow.hpp"
#include <memory>
#include <string>

struct DisplaySettings;
class MainWindow : public BaseWindow
{
    public:
        MainWindow( HINSTANCE, DisplaySettings& );
		virtual ~MainWindow() { }

        const HWND GetHWND() const { return _window; }
        const DisplaySettings& GetDisplaySettings() const { return *_ds_ptr; }
        void OnResize( DisplaySettings& );

        LRESULT CALLBACK Proc( HWND, UINT, WPARAM, LPARAM );

    protected:
        void Register();
        void Create();

        LRESULT DoKeyDownInMenu( UINT, WPARAM, LPARAM );
        LRESULT DoKeyDownInGame( UINT, WPARAM, LPARAM );

        static const unsigned int MAX_STRING_LENGTH = 100;

		std::wstring	_title;
		std::wstring	_classname;

        HWND	_window;
		bool	_is_cursor_hidden;

        std::auto_ptr< DisplaySettings >	_ds_ptr;
};

#endif  _MAIN_WINDOW_HPP_
