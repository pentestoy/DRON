/**
 *  Utility/Timer.cpp
 *  (c) Jonathan Capps
 *  Created 24 Sept. 2011
 */

#include "Timer.hpp"
#include <windows.h>

Timer::Timer()
    : _seconds_per_count( 0.0 ), _delta_time( 0.0 ), _base_time( 0 ),
	  _prev_time( 0 ), _current_time( 0 ), _paused_time( 0 ), _stop_time( 0 ),
	  _is_paused( false ), _beat_length( 60.0f / 140.0f ),
	  _time_since_last_beat( 0.0f ), _beat( 0 ), _max_beat_count( 4 )
{
    __int64 counts_per_second;
	/* I've been trying to get rid of c-style casts,
	 * but nothing seems to work here
	 */
    QueryPerformanceFrequency( ( LARGE_INTEGER* ) &counts_per_second );
    _seconds_per_count = 1.0 / static_cast< double >( counts_per_second );
}

float Timer::GetGameTime() const
{
    if( _is_paused )
        return ( float )( (_stop_time - _base_time ) * _seconds_per_count );

    else
        return ( float )( ( _current_time - _paused_time - _base_time ) * _seconds_per_count );
}

float Timer::GetDeltaTime() const
{
    return ( float )_delta_time;
}

void Timer::Reset()
{
    __int64 current_time;
    QueryPerformanceCounter( ( LARGE_INTEGER* ) &current_time );

    _base_time = current_time;
    _prev_time = current_time;
    _stop_time = 0;
    _is_paused = false;
}

void Timer::Start()
{
    __int64 time;
    QueryPerformanceCounter( ( LARGE_INTEGER* ) &time );

    if( _is_paused )
    {
        _paused_time += time - _stop_time;
        _prev_time = time;
        _stop_time = 0;
        _is_paused = false;
    }
}

void Timer::Stop()
{
    if( !_is_paused )
    {
        __int64 time;
        QueryPerformanceCounter( ( LARGE_INTEGER* ) &time );

        _stop_time = time;
        _is_paused = true;
    }
}

void Timer::Tick()
{
    if( _is_paused )
    {
        _delta_time = 0.0;
        return;
    }

    __int64 time;
    QueryPerformanceCounter( ( LARGE_INTEGER* ) &time );
    
    _current_time = time;
    _delta_time   = ( _current_time - _prev_time ) * _seconds_per_count;
    _prev_time    = _current_time;

    if( _delta_time < 0.0 )
        _delta_time = 0.0;

    //added the below for beat syncing
    _time_since_last_beat += ( float )_delta_time;
    if( _time_since_last_beat > _beat_length )
    {
        _time_since_last_beat -= _beat_length;
        ++_beat;
        if( _beat == _max_beat_count )
            _beat -= _max_beat_count;

        //_beat_trigger.emit();
    }
}
