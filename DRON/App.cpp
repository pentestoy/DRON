/**
 *  App.cpp
 *  (c) Jonathan Capps
 *  Created 06 Sept. 2011
 */

#include <Windows.h>
#include "App.hpp"
#include "Display/D3D11Renderer.hpp"
#include "Display/DisplaySettingsDialog.hpp"
#include "Display/MainWindow.hpp"
#include "Entity/EntitySystem.hpp"
#include "Utility/StringHelper.hpp"

// ============================================================================
// Create instances for all the SubSystems and Menu
// ============================================================================
App::App( HINSTANCE instance )
	: _instance( instance ), _entity_system_ptr( new EntitySystem() ),
	  _main_window_ptr( 0 )
{ }

App::~App()
{
	SAFE_DELETE( _renderer_ptr );
	SAFE_DELETE( _main_window_ptr );
	SAFE_DELETE( _entity_system_ptr );
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
		_renderer_ptr = new D3D11Renderer( _main_window_ptr->GetHWND(), ds );
	}
	catch( std::exception& e )
	{
		MessageBox( 0, StringToWString( e.what() ).c_str(),
			L"DRON Fatal Error", MB_OK | MB_ICONERROR );
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
{
	_renderer_ptr->Draw();
}