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
		MainWindow*		_main_window_ptr;
};

#endif  _APP_HPP_
