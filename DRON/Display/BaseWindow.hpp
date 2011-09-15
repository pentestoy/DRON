/**
 *  Display/BaseWindow.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef BASE_WINDOW_HPP
#define BASE_WINDOW_HPP

#include <windows.h>

LRESULT CALLBACK BaseWindowProc(HWND, UINT, WPARAM, LPARAM);

class BaseWindow
{
    public:
        BaseWindow(HINSTANCE instance, bool dlg)
            : _instance(instance), _is_dialog(dlg)
        {}

        virtual LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM) = 0;

		const HINSTANCE GetInstance() const { return _instance; }

    private:
        HINSTANCE _instance;
        bool      _is_dialog;
};

#endif  //BASE_WINDOW_HPP
