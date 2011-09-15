/**
 *  Display/MainWindow.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include "BaseWindow.hpp"
#include <memory>
#include <string>

struct DisplaySettings;
class App;
class MainWindow : public BaseWindow
{
    public:
        MainWindow( HINSTANCE instance, App& app, DisplaySettings& ds );
		virtual ~MainWindow() { }

        const HWND GetHWND() const { return _window; }
        const DisplaySettings& GetDisplaySettings() const { return *_ds_ptr; }
        void OnResize( DisplaySettings& );

        virtual LRESULT CALLBACK Proc( HWND, UINT, WPARAM, LPARAM );

    private:
        void Register();
        void Create();

        LRESULT DoKeyDownInMenu( UINT, WPARAM, LPARAM );
        LRESULT DoKeyDownInGame( UINT, WPARAM, LPARAM );

        static const unsigned int MAX_STRING_LENGTH = 100;

        HWND	_window;
		bool	_is_cursor_hidden;
		App&	_app;

		std::wstring	_title;
		std::wstring	_classname;

        std::auto_ptr< DisplaySettings >	_ds_ptr;
};

#endif  //MAIN_WINDOW_HPP
