#pragma once
#include <ArcSynth/precompiled.h>

///
/// \brief Timer class that gets high-precision time
///
/// Currently windows-specific. Uses QueryPerformanceCounter and QueryPerformanceFrequency to get
/// clock counts, which are then compared to an frame of reference. The times are returned in
/// double-precision seconds.
///
class Timer
{
public:
    Timer();

    ///
    /// \brief Initializes the timer and sets the counter to zero
    ///
    /// Gets the current timer query and stores it as the reference point for the timer.
    ///
    void SetTime( void );
    
    ///
    /// \brief Gets the time since the reference point time.
    ///
    /// Calculates the time (in double-precision seconds) since the timer was initialized or reset.
    /// Returns -1 if the timer has not been initialized.
    ///
    double GetTime( void );

    ///
    /// \brief Gets the time since GetDeltaTime has been called
    ///
    /// Used to get times (in double-precision seconds) between marked points in code (used for frame-times primarily.)
    ///
    double GetDeltaTime( void );

    ///
    /// \brief Resets the base time reference point without affecting the delta reference point.
    ///
    /// Resets clocks so that subsequent calls to GetTime refer to this
    /// call point as the reference point. Returns the time since the last reset.
    ///
    double ResetBaseTime( void );

    ///
    /// \brief Returns true if the timer is ready to get values
    ///
    bool IsInitialized( void );

private:

    ///
    /// \brief gets the double-precision time difference.
    /// 
    /// Gets the difference between either the base clock reference point or the delta reference point
    /// and returns a double-precision value in seconds 
    ///
    double getTimeDifference( bool delta );

    /// Reference point for storing the time since the timer was initialized/reset
    __int64 timerReferencePoint;

    /// Reference point for the last time GetDeltaTime was called
    __int64 deltaReferencePoint;

    /// Flag is set to true once we set the reference points (otherwise times would make no sense.)
    bool isInitialized;
};