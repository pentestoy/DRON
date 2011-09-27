/**
 *  App.hpp
 *  (c) Jonathan Capps
 *  Created 06 Sept. 2011
 *
 *  Only create one instance of this class.
 */

#ifndef APP_HPP
#define APP_HPP

#include <Windows.h>
#include "Utility/Timer.hpp"

#define SAFE_DELETE( x ) if( x ){ delete x; x = 0; }

typedef unsigned int Entity;

class D3D11Renderer;
class EntitySystem;
class GameState;
class MainWindow;
class Menu;
class World;
class App
{
    public:
        App( HINSTANCE );
		~App();

        int Run();
		void HandleKeypress( const WPARAM key );

    protected:
        //prevent copies
        App( const App& );
        App& operator=( const App& );

        bool Initialize();

		HINSTANCE		_instance;
		EntitySystem*	_entity_system_ptr;
		MainWindow*		_main_window_ptr;
		D3D11Renderer*	_renderer_ptr;

		Menu*			_menu_ptr;
		World*			_world_ptr;
		GameState*		_current_state_ptr;

		Timer			_timer;
};

#endif  APP_HPP
