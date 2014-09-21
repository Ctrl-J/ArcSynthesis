#pragma once
#include <ArcSynth/precompiled.h>

class Logger;

enum class BUTTON_TYPE
{
    Left     = 1,
    Middle   = 1 << 1,
    Right    = 1 << 2,
    Forward  = 1 << 3,
    Back     = 1 << 4
};

class Mouse
{
    friend class Application;
public:
    Mouse( std::shared_ptr<Logger> logger_ptr );

    glm::vec2 GetMouseDelta( void ) const;
    bool IsButtonDown( BUTTON_TYPE buttons );
    bool IsButtonPressed( BUTTON_TYPE buttons );

private:
    void setMouseDelta( float delta_x, float delat_y );
    void setButtonDown( BUTTON_TYPE buttons, bool is_down );
    void setButtonPressed( BUTTON_TYPE buttons, bool is_pressed );
    void setButtonUp( BUTTON_TYPE buttons );

    std::array<bool, 5> downButtons;
    std::array<bool, 5> pressedButtons;
    glm::vec2 mouseDelta;

    std::shared_ptr<Logger> logger;
};
