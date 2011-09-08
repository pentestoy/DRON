/**
 *  App.hpp
 *  (c) Jonathan Capps
 *  Created 06 Sept. 2011
 *
 *  Only create one instance of this class.
 */

#ifndef _APP_HPP_
#define _APP_HPP_

#include <Windows.h>

#define SAFE_DELETE( x ) if( x ){ delete x; x = 0; }

class D3D11Renderer;
class EntitySystem;
class MainWindow;
class App
{
    public:
        App( HINSTANCE );
		~App();

        int Run();

    protected:
        //prevent copies
        App( const App& );
        App& operator=( const App& );

        bool Initialize();
		void Update( float );

		HINSTANCE		_instance;
		EntitySystem*	_entity_system_ptr;
		MainWindow*		_main_window_ptr;
		D3D11Renderer*	_renderer_ptr;

};

#endif  _APP_HPP_
