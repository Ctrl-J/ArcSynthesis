#pragma once
#include <ArcSynth\precompiled.h>
#include <ArcSynth\Abstracts\chapter.h>
#include <ArcSynth\OpenGL\shader_manager.h>
#include <ArcSynth\Objects\free_camera.h>

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

    glm::mat4 modelMatrix;
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    std::shared_ptr<FreeCamera> camera;
    glm::vec3 cameraVelocity;

    float cameraDrag;
    float cameraAcceleration;

    float fov;
    float aspectRatio;
    float nearClipPlane;
    float farClipPlane;

    void setFOV( float new_fov );
    void setClipPlanes( float near_plane, float far_plane );

    glm::mat4 getViewMatrix( void );
    glm::mat4 getProjectionMatrix( void );

    GLuint shaderId;

    GLuint vertexBufferObject;
    GLuint vertexArrayObject;

    GLuint modelMatrixUniformObject;
    GLuint viewMatrixUniformObject;
    GLuint projectionMatrixUniformObject;
};
