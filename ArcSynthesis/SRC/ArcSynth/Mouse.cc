#include <ArcSynth\precompiled.h>
#include <ArcSynth\logger.h>
#include <ArcSynth\mouse.h>

Mouse::Mouse( std::shared_ptr<Logger> set_logger )
{
    logger = set_logger;
}

glm::vec2 Mouse::GetMouseDelta( void ) const
{
    return mouseDelta;
}

bool Mouse::IsButtonDown( BUTTON_TYPE buttons )
{
    return true;
}

bool Mouse::IsButtonPressed( BUTTON_TYPE buttons )
{
    return true;
}

void Mouse::setMouseDelta( float delta_x, float delta_y )
{
    mouseDelta.x = delta_x;
    mouseDelta.y = delta_y;
}

void Mouse::setButtonDown( BUTTON_TYPE buttons, bool is_down )
{
}

void Mouse::setButtonPressed( BUTTON_TYPE buttons, bool is_pressed )
{
}

void Mouse::setButtonUp( BUTTON_TYPE buttons )
{
}

