/**
 *  Display/BaseWindow.hpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#ifndef _BASE_WINDOW_HPP_
#define _BASE_WINDOW_HPP_

#include <windows.h>

LRESULT CALLBACK BaseWindowProc(HWND, UINT, WPARAM, LPARAM);

class BaseWindow
{
    public:
        BaseWindow(HINSTANCE instance, bool dlg)
            : _instance(instance), _is_dialog(dlg)
        {}

        virtual LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM) = 0;

    protected:
        HINSTANCE _instance;
        bool      _is_dialog;
};

#endif  _BASE_WINDOW_HPP_
