#include <precompiled.h>
#include <chapter_one.h>

ChapterOne::ChapterOne( std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Configuration> config_ptr ) 
    : Chapter( keyboard_ptr, config_ptr )
{
}

ChapterOne::~ChapterOne()
{
}

void ChapterOne::Initialize( void )
{
    color = glm::vec3( 0.2, 0.4, 0.45 );
    speed = glm::vec3( 0.2, 0.25, 0.25 );
}

void ChapterOne::Draw( void )
{
    glClearColor( color.r, color.g, color.b, 1.0 );
}

void ChapterOne::Step( double time_step )
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

void ChapterOne::Shutdown( void )
{
}