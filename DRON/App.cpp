/**
 *  App.cpp
 *  (c) Jonathan Capps
 *  Created 06 Sept. 2011
 */

#include <algorithm>
#include <Windows.h>
#include "App.hpp"
#include "Display/DisplaySettingsDialog.hpp"
#include "Display/MainWindow.hpp"
#include "Utility/StringHelper.hpp"

// ============================================================================
// Create instances for all the SubSystems and Menu
// ============================================================================
App::App( HINSTANCE instance )
	: _instance( instance ), _main_window_ptr( 0 )
{ }

App::~App()
{
	if( _main_window_ptr )
	{
		delete _main_window_ptr;
		_main_window_ptr = 0;
	}
}

bool App::Initialize()
{
	DisplaySettingsDialog dsd( _instance );
	if( !dsd.Show() )
		return false;

	DisplaySettings ds = dsd.GetDisplaySettings();
	try
	{
		_main_window_ptr = new MainWindow( _instance, ds );
	}
	catch( std::exception& e )
	{
		MessageBox( 0, StringToWString( e.what() ).c_str(), L"DRON Fatal Error", MB_OK | MB_ICONERROR );
		return false;
	}

	return true;
}

// ============================================================================
// Calling this enters the game loop
// ============================================================================
int App::Run()
{
    if( !Initialize() )
		return 0;

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		float dt = 0.0f;
		Update( dt );
	}

	return msg.wParam;
}

void App::Update( float dt )
{ }