#pragma once
#include <ArcSynth\precompiled.h>
#include <ArcSynth\Abstracts\render_model.h>

class DemoCube : public RenderModel
{
public:

    DemoCube( std::shared_ptr<Logger> logger );
    ~DemoCube( void );
    DemoCube( const DemoCube &other ) = delete;
    DemoCube &operator= ( const DemoCube &other ) = delete;

    bool Initialize( void );
    void Draw( void );
    void Shutdown( void );
    void SetFaceColor( int index, const glm::vec4 &color );
    glm::vec4 GetFaceColor( int index ) const;

private:
    void initArrays( void );

    std::vector<glm::vec4> vertexData;
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;


};