#pragma once
#include <precompiled.h>
#include <chapter.h>
#include <shader_manager.h>

class ChapterData;

class ChapterOne : public Chapter
{
public:
    ChapterOne( const std::string &chapter_filename, std::shared_ptr<Configuration> config_ptr,
                std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    ~ChapterOne();
    ChapterOne( const ChapterOne &other ) = delete;
    ChapterOne &operator= ( const ChapterOne &other ) = delete;

    void Initialize( void );
    void Draw( void );
    void Step( double time_step );
    void Shutdown( void );

private:

    void initArrays( void );

    glm::vec3 color;
    std::string filename;
    std::shared_ptr<ChapterData> chapterData;
    std::shared_ptr<ShaderManager> shaderManager;

    std::vector<float> vertexData;

    GLuint position_buffer_object;
    GLuint vertex_array_object;
};
