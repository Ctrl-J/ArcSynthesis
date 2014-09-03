#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_zero.h>

ChapterZero::ChapterZero( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
}

ChapterZero::~ChapterZero()
{
}

void ChapterZero::Initialize( void )
{
    color = glm::vec3( 0.2, 0.4, 0.45 );
    speed = glm::vec3( 0.2, 0.25, 0.25 );
}

void ChapterZero::Draw( void )
{
    glClearColor( color.r, color.g, color.b, 1.0 );
}

void ChapterZero::Step( double time_step )
{
    color += speed * static_cast<float>( time_step );
    if( color.r >= 1.0 )
    {
        color.r = 1.0;
        speed.r = -speed.r;
    }
    else if( color.r <= 0.0 )
    {
        color.r = 0.0;
        speed.r = -speed.r;
    }
    if( color.g >= 1.0 )
    {
        color.g = 1.0;
        speed.g = -speed.g;
    }
    else if( color.g <= 0.0 )
    {
        color.g = 0.0;
        speed.g = -speed.g;
    }
    if( color.b >= 1.0 )
    {
        color.b = 1.0;
        speed.b = -speed.b;
    }
    else if( color.b <= 0.0 )
    {
        color.b = 0.0;
        speed.b = -speed.b;
    }
}

void ChapterZero::Shutdown( void )
{
}