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
#include <memory>
#include "Entity/Entity.hpp"
#include "Utility/Timer.hpp"

class D3D11Renderer;
class EntitySystem;
class GameState;
class MainWindow;
class Menu;
class Script;
class World;
class App
{
    public:
        App( HINSTANCE );
		~App();

        int Run();
		void HandleKeypress( const WPARAM key );

    private:
        //prevent copies
        App( const App& );
        App& operator=( const App& );

        bool Initialize();

		HINSTANCE		_instance;
		std::shared_ptr< EntitySystem >  _entity_system_ptr;
		std::shared_ptr< D3D11Renderer > _renderer_ptr;
		std::unique_ptr< MainWindow >	 _main_window_ptr;
		std::shared_ptr< Script >		 _script_ptr;

		/*
		Menu*			_menu_ptr;
		World*			_world_ptr;
		GameState*		_current_state_ptr;
		*/
		std::shared_ptr< GameState > _menu_ptr;
		std::shared_ptr< GameState > _world_ptr;
		std::shared_ptr< GameState > _current_state_ptr;

		Timer			_timer;
};

#endif  APP_HPP
