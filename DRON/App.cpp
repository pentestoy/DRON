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
#include "Resource/PixelShaderManager.hpp"
#include "Resource/VertexShaderManager.hpp"
#include "Utility/StringHelper.hpp"

App::App( HINSTANCE instance )
	: _instance( instance ), _entity_system_ptr( new EntitySystem() ),
	  _main_window_ptr( 0 ), _renderer_ptr( 0 ), _menu_ptr( 0 ),
	  _world_ptr( 0 ), _current_state_ptr( 0 ), _ps_manager_ptr( 0 ),
	  _vs_manager_ptr( 0 )
{ }

App::~App()
{
	SAFE_DELETE( _renderer_ptr );
	SAFE_DELETE( _vs_manager_ptr );
	SAFE_DELETE( _ps_manager_ptr );
	SAFE_DELETE( _main_window_ptr );
	SAFE_DELETE( _menu_ptr );
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
		_main_window_ptr = new MainWindow( _instance, *this, ds );
	}
	catch( std::exception& e )
	{
		MessageBox( 0, StringToWString( e.what() ).c_str(),
			L"DRON Fatal Error", MB_OK | MB_ICONERROR );
		return false;
	}

	_ps_manager_ptr = new PixelShaderManager();
	_vs_manager_ptr = new VertexShaderManager();
	_renderer_ptr = new D3D11Renderer( _main_window_ptr->GetHWND(),
									   ds,
									   *_ps_manager_ptr,
									   *_vs_manager_ptr );
	_menu_ptr = new Menu( *_entity_system_ptr, *_renderer_ptr );
	_current_state_ptr = _menu_ptr;

	return true;
}

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
		_current_state_ptr->Update( dt );
	}

	return msg.wParam;
}

void App::HandleKeypress( const WPARAM key )
{
	_current_state_ptr->HandleKeypress( key );
}
