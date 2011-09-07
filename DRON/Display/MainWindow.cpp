/**
 *  Display/MainWindow.cpp
 *  (c) Jonathan Capps
 *  Created 07 Sept. 2011
 */

#include "MainWindow.hpp"
#include "DisplaySettingsDialog.hpp"
#include "../resource.h"

MainWindow::MainWindow( HINSTANCE instance, DisplaySettings& ds )
	: BaseWindow( instance, false ), _ds_ptr( new DisplaySettings( ds ) ),
	  _is_cursor_hidden( false )

{
	_title.assign( MAX_STRING_LENGTH, L'\n' );
	_classname.assign( MAX_STRING_LENGTH, L'\n' );
    LoadString( _instance, IDS_APP_TITLE, &_title[ 0 ], MAX_STRING_LENGTH );
    LoadString( _instance, IDC_DRON, &_classname[ 0 ], MAX_STRING_LENGTH );

	Register();
	Create();
}

void MainWindow::Register()
{
	WNDCLASSEX wcx;

	wcx.cbSize        = sizeof( wcx );
	wcx.style		  = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc	  = BaseWindowProc;
	wcx.cbClsExtra	  = 0;
	wcx.cbWndExtra	  = 0;
	wcx.hInstance	  = _instance;
	wcx.hIcon		  = LoadIcon( _instance, MAKEINTRESOURCE( IDC_DRON ) );
	wcx.hCursor		  = LoadCursor( NULL, IDC_ARROW );
	wcx.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1 );
	wcx.lpszMenuName  = 0;
	wcx.lpszClassName = &_classname[ 0 ];
	wcx.hIconSm		  = LoadIcon( _instance, MAKEINTRESOURCE( IDI_SMALL ) );

	if( !RegisterClassEx( &wcx ) )
		throw std::exception( "Failed to register the window class!" );
}

void MainWindow::Create()
{
    RECT r;
    SetRect( &r, 0, 0, _ds_ptr->_width, _ds_ptr->_height );
    AdjustWindowRect( &r, WS_OVERLAPPEDWINDOW, false );

    _window = CreateWindow( &_classname[ 0 ], &_title[ 0 ],
                           WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU |
                           WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
                           CW_USEDEFAULT, 0, r.right - r.left, r.bottom - r.top,
                           0, 0, _instance, this );

	/**************************************************************************
	 *
	 * throwing an exception after calling CreateWindwo causes an access
	 * violation. Don't understand why, but we're just oing to comment it out
	 * and assume it succeeds for now. :(

	if ( !_window )
		throw std::exception( "Failed to create the window!" );

	 **************************************************************************/

	ShowWindow( _window, SW_SHOW );
	UpdateWindow(_window);
}

void MainWindow::OnResize( DisplaySettings& ds )
{
    _ds_ptr.reset( new DisplaySettings( ds ) );

    RECT r;
    SetRect( &r, 0, 0, ds._width, ds._height );
    AdjustWindowRect( &r, WS_OVERLAPPEDWINDOW, false );

	/**************************************************************************
	 * Ideally, this should be centered, taking into accoung the resolution of
	 * the screen on which the app is being displayed.
	 */
    SetWindowPos( _window, HWND_TOP, 0, 0, r.right - r.left, r.bottom - r.top, SWP_NOMOVE | SWP_NOZORDER );
}

LRESULT CALLBACK MainWindow::Proc( HWND window, UINT message, WPARAM wParam, LPARAM lParam )
{
	switch ( message )
	{
	    case WM_COMMAND:
		    switch ( LOWORD( wParam ) )
		    {
		        case IDM_EXIT:
			        DestroyWindow( _window );
			        break;
		        default:
			        return DefWindowProc( _window, message, wParam, lParam );
		    }
		    break;

        case WM_KEYDOWN:
            //_app.GetCurrentGameState().HandleMessages( window, message, wParam, lParam );
            break;

		case WM_SETCURSOR:
		{
			WORD hit_test = LOWORD( lParam );
			if ( hit_test == HTCLIENT && !_is_cursor_hidden )
			{
				_is_cursor_hidden = true;
				ShowCursor( false );
			}
			else if ( hit_test != HTCLIENT && _is_cursor_hidden ) 
			{
				_is_cursor_hidden = false;
				ShowCursor( true );
			}
		}
		break;

	    case WM_DESTROY:
		    PostQuitMessage( 0 );
		    break;

	    default:
		    return DefWindowProc( _window, message, wParam, lParam );
	}
	return 0;
}
