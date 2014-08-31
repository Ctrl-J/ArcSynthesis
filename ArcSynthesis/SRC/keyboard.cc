#include <precompiled.h>
#include <keyboard.h>

Keyboard::Keyboard()
{
    std::fill( downKeys.begin(), downKeys.end(), false );
    std::fill( pressedKeys.begin(), pressedKeys.end(), false );
}

bool Keyboard::IsKeydown( int key_code )
{
    // if the key code is out of range, there's no way the key can be down.
    if( ( key_code < 0 ) || ( key_code >= KEY_COUNT ) )
    {
        return false;
    }

    return downKeys[ key_code ];
}

bool Keyboard::IsKeyPressed( int key_code )
{
    if( ( key_code < 0 ) || ( key_code >= KEY_COUNT ) )
    {
        return false;
    }

    bool is_pressed = pressedKeys[key_code];
    // this could be called much faster than the messages come in, so be sure to
    // only allow this to be fired once;
    pressedKeys[key_code] = false;

    return is_pressed;
}

void Keyboard::setKeyDown( int key_code )
{
    if( ( key_code >= 0 ) && ( key_code < KEY_COUNT ) )
    {
        downKeys[key_code] = true;
    }
}

void Keyboard::setKeyPressed( int key_code, bool is_pressed )
{
    if( ( key_code >= 0 ) && ( key_code < KEY_COUNT ) )
    {
        pressedKeys[key_code] = is_pressed;
    }
}

void Keyboard::setKeyUp( int key_code )
{
    if( ( key_code >= 0 ) && ( key_code < KEY_COUNT ) )
    {
        downKeys[key_code] = false;
        pressedKeys[key_code] = false;
    }
}