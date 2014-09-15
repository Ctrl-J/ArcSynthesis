#pragma once
#include <ArcSynth/precompiled.h>
#include <ArcSynth/Abstracts/chapter.h>
#include <ArcSynth/OpenGL/shader_manager.h>

class ChapterData;

class ChapterTwo : public Chapter
{
public:
    ChapterTwo( const std::string &chapter_filename, std::shared_ptr<Configuration> config_ptr,
                std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    ~ChapterTwo();
    ChapterTwo( const ChapterTwo &other ) = delete;
    ChapterTwo &operator= ( const ChapterTwo &other ) = delete;

    void Initialize( void );
    void Draw( void );
    void Step( float time_step );
    void Shutdown( void );

private:

    void initArrays( void );

    glm::vec3 color;
    std::string filename;
    std::shared_ptr<ChapterData> chapterData;
    std::shared_ptr<ShaderManager> shaderManager;

    std::vector<glm::vec4> positionData;
    std::vector<glm::vec4> colorData;

    GLuint position_buffer_object;
    GLuint color_buffer_object;
    GLuint vertex_array_object;
};
