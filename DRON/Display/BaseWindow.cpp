/**
 *  Display/BaseWindow.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include "BaseWindow.hpp"

LRESULT CALLBACK BaseWindowProc(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if(msg == WM_INITDIALOG)
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)lParam);

    else if(msg == WM_CREATE)
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)((LPCREATESTRUCT)lParam)->lpCreateParams);

    BaseWindow* bw = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(window, GWLP_USERDATA));
    
    ////////////////////////////////////////////////////////
    //
    // WM_SETFONT is sent to dialogs *before WM_INITDIALOG
    // so we can't just return bw->Proc
    // this works, but I'm not sure it's the best solutioin
    //

    if(bw)
        return bw->Proc(window, msg, wParam, lParam);

    return DefWindowProc(window, msg, wParam, lParam);
}