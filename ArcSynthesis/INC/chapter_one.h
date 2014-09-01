#pragma once
#include <precompiled.h>
#include <chapter.h>

class ChapterOne : public Chapter
{
public:
    ChapterOne( std::shared_ptr<Configuration> config_ptr, std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    ~ChapterOne();
    ChapterOne( const ChapterOne &other ) = delete;
    ChapterOne &operator= ( const ChapterOne &other ) = delete;

    void Initialize( void );
    void Draw( void );
    void Step( double time_step );
    void Shutdown( void );

private:
    glm::vec3 color;
    glm::vec3 speed;
};