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

    // this gives us the clocks per second.
    double timing_frequency = static_cast< double >( timing_query.QuadPart );

    QueryPerformanceCounter( &timing_query );
    timerReferencePoint = timing_query.QuadPart;
    deltaReferencePoint = timing_query.QuadPart;

    isInitialized = true;
}

double Timer::GetTime( void )
{
    if( isInitialized == false )
    {
        return -1.0;
    }

    return getTimeDifference( false );
}

double Timer::GetDeltaTime( void )
{
    if( isInitialized == false )
    {
        return -1.0;
    }

    return getTimeDifference( true );
}

double Timer::ResetBaseTime( void )
{
    LARGE_INTEGER timing_query;
    // we could error check here, but according to MSDN, on systems running WindowsXP or later this will never fail.
    QueryPerformanceFrequency( &timing_query ); 

    // this gives us the clocks per second.
    double timing_frequency = static_cast< double >( timing_query.QuadPart );

    QueryPerformanceCounter( &timing_query );
    double time = getTimeDifference( false );
    timerReferencePoint = timing_query.QuadPart;

    return time;
}

bool Timer::IsInitialized( void )
{
    return isInitialized;
}

double Timer::getTimeDifference( bool delta )
{
    LARGE_INTEGER timing_query;
    QueryPerformanceFrequency( &timing_query ); 
    double timing_frequency = static_cast< double >( timing_query.QuadPart );
    
    QueryPerformanceCounter( &timing_query ); 

    double time = -1;

    if( delta )
    {
        time = static_cast< double >( timing_query.QuadPart - deltaReferencePoint ) / timing_frequency;
    }
    else
    {
        time = static_cast< double >( timing_query.QuadPart - timerReferencePoint ) / timing_frequency;
    }

    return time;    
}