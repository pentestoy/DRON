/**
 *  App.cpp
 *  (c) Jonathan Capps
 *  Created 06 Sept. 2011
 */

#include "App.hpp"
#include "Display/D3D11Renderer.hpp"
#include "Display/DisplaySettingsDialog.hpp"
#include "Display/MainWindow.hpp"
#include "Entity/EntitySystem.hpp"
#include "GameState/Menu.hpp"
#include "Script/Script.hpp"
#include "Utility/StringHelper.hpp"

App::App( HINSTANCE instance )
	: _instance( instance ), _entity_system_ptr( new EntitySystem() ),
	  _script_ptr( new Script( "Data/Scripts/" ) )
{ }

App::~App()
{
	CoUninitialize();
}

bool App::Initialize()
{
	CoInitializeEx( 0, COINIT_APARTMENTTHREADED );

	DisplaySettingsDialog dsd( _instance );
	if( !dsd.Show() )
		return false;

	DisplaySettings ds = dsd.GetDisplaySettings();
	try
	{
		_main_window_ptr.reset( new MainWindow( _instance, *this, ds ) );
	}
	catch( std::exception& e )
	{
		MessageBox( 0, StringToWString( e.what() ).c_str(),
			L"DRON Fatal Error", MB_OK | MB_ICONERROR );
		return false;
	}

	_renderer_ptr.reset( new D3D11Renderer(
		_main_window_ptr->GetHWND(),
		ds,
		*_entity_system_ptr ) );
	_menu_ptr.reset( new Menu( *_entity_system_ptr, *_renderer_ptr, *_script_ptr ) );
	_current_state_ptr = _menu_ptr;

	_timer.Reset();

	return true;
}

int App::Run()
{
    if( !Initialize() )
	{
		MessageBox( 0, L"DRON failed to properly initialize and must shut down.", L"DRON Fatal Error", MB_OK | MB_ICONEXCLAMATION );
		return 0;
	}

	MSG msg = {0};
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		_timer.Tick();
		_current_state_ptr->Update( _timer.GetDeltaTime() );
	}

	return msg.wParam;
}

void App::HandleKeypress( const WPARAM key )
{
	_current_state_ptr->HandleKeypress( key );
}
