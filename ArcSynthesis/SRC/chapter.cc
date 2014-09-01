#include <precompiled.h>
#include <chapter.h>

Chapter::Chapter( std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Configuration> config_ptr )
{
    keyboard = keyboard_ptr;
    config = config_ptr;
}

Chapter::~Chapter()
{
}