#include <ArcSynth/precompiled.h>
#include <ArcSynth/Abstracts/chapter.h>

Chapter::Chapter( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr )
{
    config = config_ptr;
    keyboard = keyboard_ptr;
    logger = logger_ptr;
    initialized = false;
}

Chapter::~Chapter()
{
}

bool Chapter::IsInitialized( void ) const
{
    return initialized;
}