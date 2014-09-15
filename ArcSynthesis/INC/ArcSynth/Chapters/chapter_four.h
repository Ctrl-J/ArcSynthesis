#pragma once
#include <ArcSynth/precompiled.h>
#include <ArcSynth/Abstracts/chapter.h>
#include <ArcSynth/OpenGL/shader_manager.h>

class ChapterData;

class ChapterFour : public Chapter
{
public:
    ChapterFour( const std::string &chapter_filename, std::shared_ptr<Configuration> config_ptr,
                 std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    ~ChapterFour();
    ChapterFour( const ChapterFour &other ) = delete;
    ChapterFour &operator= ( const ChapterFour &other ) = delete;

    void Initialize( void );
    void Draw( void );
    void Step( float time_step );
    void Shutdown( void );

private:

    void initArrays( void );

    std::string filename;
    std::shared_ptr<ChapterData> chapterData;
    std::shared_ptr<ShaderManager> shaderManager;
    glm::vec3 positionSpeed;

    std::vector<glm::vec4> vertexData;

    GLuint vertex_buffer_object;
    GLuint vertex_array_object;
};
