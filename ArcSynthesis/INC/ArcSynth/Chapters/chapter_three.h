#pragma once
#include <ArcSynth/precompiled.h>
#include <ArcSynth/Abstracts/chapter.h>
#include <ArcSynth/OpenGL/shader_manager.h>

class ChapterData;

class ChapterThree : public Chapter
{
public:
    ChapterThree( const std::string &chapter_filename, std::shared_ptr<Configuration> config_ptr,
                std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr );
    ~ChapterThree();
    ChapterThree( const ChapterThree &other ) = delete;
    ChapterThree &operator= ( const ChapterThree &other ) = delete;

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
    glm::vec3 positionSpeed;

    std::vector<glm::vec4> positionData;
    std::vector<glm::vec4> colorData;
    std::vector<float> colorSpeed;

    glm::vec3 colorShiftDirection;
    glm::vec3 colorShiftUniform;

    GLuint colorShiftUniformObject;

    GLuint position_buffer_object;
    GLuint color_buffer_object;
    GLuint vertex_array_object;
};
