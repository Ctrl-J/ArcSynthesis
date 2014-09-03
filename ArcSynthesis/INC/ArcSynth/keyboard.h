#pragma once
#include <ArcSynth/precompiled.h>

class Logger;

class Keyboard
{
    friend class Application;
public:
    Keyboard( std::shared_ptr<Logger> logger_ptr );

    ///
    /// \brief Gets the status of the given key.
    ///
    /// This will return true as long as the key is down.
    ///
    bool IsKeydown( int key_code );
    
    ///
    /// \brief Gets the first time a key is down. 
    ///
    /// This will return true once per key down.
    ///
    bool IsKeyPressed( int key_code );

private:
    /// Sets the key down state for the given key code
    void setKeyDown( int key_code );
    /// Sets the key pressed state for the given key code
    void setKeyPressed( int key_code, bool is_pressed );
    /// Sets the key up state for the given key code
    void setKeyUp( int key_code );

    std::array<bool, KEY_COUNT> downKeys;
    std::array<bool, KEY_COUNT> pressedKeys;

    std::shared_ptr<Logger> logger;
};