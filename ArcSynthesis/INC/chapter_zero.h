#pragma once
#include <precompiled.h>
#include <chapter.h>

class ChapterZero : public Chapter
{
public:
    ChapterZero( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    ~ChapterZero();
    ChapterZero( const ChapterZero &other ) = delete;
    ChapterZero &operator= ( const ChapterZero &other ) = delete;

    void Initialize( void );
    void Draw( void );
    void Step( double time_step );
    void Shutdown( void );

private:
    glm::vec3 color;
    glm::vec3 speed;
};