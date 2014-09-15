#include <ArcSynth/precompiled.h>
#include <ArcSynth/timer.h>

Timer::Timer()
{
    timerReferencePoint = 0;
    deltaReferencePoint = 0;
}

void Timer::SetTime( void )
{
    LARGE_INTEGER timing_query;
    // we could error check here, but according to MSDN, on systems running WindowsXP or later this will never fail.
    QueryPerformanceFrequency( &timing_query ); 

    QueryPerformanceCounter( &timing_query );
    timerReferencePoint = timing_query.QuadPart;
    deltaReferencePoint = timing_query.QuadPart;

    isInitialized = true;
}

float Timer::GetTime( void )
{
    if( isInitialized == false )
    {
        return -1.0f;
    }

    return getTimeDifference( false );
}

float Timer::GetDeltaTime( void )
{
    if( isInitialized == false )
    {
        return -1.0f;
    }

    return getTimeDifference( true );
}

float Timer::ResetBaseTime( void )
{
    LARGE_INTEGER timing_query;
    // we could error check here, but according to MSDN, on systems running WindowsXP or later this will never fail.
    QueryPerformanceFrequency( &timing_query ); 

    QueryPerformanceCounter( &timing_query );
    float time = getTimeDifference( false );
    timerReferencePoint = timing_query.QuadPart;

    return time;
}

bool Timer::IsInitialized( void )
{
    return isInitialized;
}

float Timer::getTimeDifference( bool delta )
{
    LARGE_INTEGER timing_query;
    QueryPerformanceFrequency( &timing_query ); 
    float timing_frequency = static_cast< float >( timing_query.QuadPart );
    
    QueryPerformanceCounter( &timing_query ); 

    float time = -1;

    if( delta )
    {
        time = static_cast< float >( timing_query.QuadPart - deltaReferencePoint ) / timing_frequency;
    }
    else
    {
        time = static_cast< float >( timing_query.QuadPart - timerReferencePoint ) / timing_frequency;
    }

    return time;    
}