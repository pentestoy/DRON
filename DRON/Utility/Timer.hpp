/**
 *  Utility/Timer.hpp
 *  (c) Jonathan Capps
 *  Created 24 Sept. 2011
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

//#include <sigc++/sigc++.h>

class Timer
{
    public:
        Timer();

        float GetGameTime() const;
        float GetDeltaTime() const;

        void Reset();
        void Start();
        void Stop();
        /* Increment's the Timer. Should be called at the beginning of every
           update cycle. */
        void Tick();
        
		/*
		template< typename T >
		void RegisterListener( T& thing, void( T::*func )() )
		{
			_beat_trigger.connect( sigc::mem_fun( thing, func ) );
		}
		*/

        float GetTimeSinceLastBeat() const { return _time_since_last_beat; }
        float GetBeatLength() const { return _beat_length; }
        unsigned int GetBeatCount() const { return _beat; }

    protected:
        double  _seconds_per_count;
        double  _delta_time;

        float         _beat_length;
        float         _time_since_last_beat;
        unsigned int  _beat;
        unsigned int  _max_beat_count;

        __int64  _base_time;
        __int64  _prev_time;
        __int64  _current_time;
        __int64  _paused_time;
        __int64  _stop_time;

        bool    _is_paused;

        //sigc::signal< void > _init_trigger;
        //sigc::signal< void > _beat_trigger;
};

#endif //TIMER_APP_
