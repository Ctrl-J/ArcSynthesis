#pragma once
#include <precompiled.h>

class Keyboard;
class Configuration;

class Chapter
{
public:
    Chapter( std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Configuration> config_ptr );
    ~Chapter( void );
    Chapter( const Chapter &other ) = delete;
    Chapter&operator= ( const Chapter &other ) = delete;

    virtual void Initialize( void ) = 0;
    virtual void Draw( void ) = 0;
    virtual void Step( double time_step ) = 0;
    virtual void Shutdown( void ) = 0;

protected:
    std::shared_ptr<Keyboard> keyboard;
    std::shared_ptr<Configuration> config;
};