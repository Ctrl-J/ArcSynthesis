#pragma once
#include <ArcSynth/precompiled.h>

class Configuration;
class Keyboard;
class Logger;

class Chapter
{
public:
    Chapter( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    virtual ~Chapter( void );
    Chapter( const Chapter &other ) = delete;
    Chapter&operator= ( const Chapter &other ) = delete;

    virtual void Initialize( void ) = 0;
    virtual void Draw( void ) = 0;
    virtual void Step( float time_step ) = 0;
    virtual void Shutdown( void ) = 0;
    
    bool IsInitialized( void ) const;

protected:
    std::shared_ptr<Keyboard> keyboard;
    std::shared_ptr<Configuration> config;
    std::shared_ptr<Logger> logger;

    bool initialized;
};