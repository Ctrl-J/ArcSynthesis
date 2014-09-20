#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_four.h>
#include <ArcSynth/Config/config.h>
#include <ArcSynth/Config/chapter_data.h>
#include <ArcSynth/keyboard.h>

ChapterFour::ChapterFour( const std::string &data_filename, std::shared_ptr<Configuration> config_ptr, 
                        std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
    camera = std::make_shared<FreeCamera>( logger_ptr );
    filename = data_filename;
}

ChapterFour::~ChapterFour()
{
}

void ChapterFour::Initialize( void )
{
    chapterData = std::make_shared<ChapterData>( config, logger );
    chapterData->LoadData( filename );

    shaderManager = std::make_shared<ShaderManager>( logger );
    int chapter_shader_count = chapterData->GetShaderCount();
    for( int shader_index = 0; shader_index < chapter_shader_count; shader_index++ )
    {
        if( shaderManager->LoadShader( chapterData->GetShaders().at( shader_index ) ) == false )
        {
            logger->Log( LOG_TYPE::ERR, "Chapter Error", "Error loading shaders." );
        }
    }

    shaderId = shaderManager->GetShaderByName( "basic" );
    if( shaderId == UINT32_MAX )
    {
        initialized = false;
        return;
    }

    camera->Initialize();

    cameraAcceleration = 1.25f;
    cameraDrag = 0.75f;

    modelMatrixUniformObject = glGetUniformLocation( shaderId, "model" );
    viewMatrixUniformObject = glGetUniformLocation( shaderId, "view" );
    projectionMatrixUniformObject = glGetUniformLocation( shaderId, "projection" );

    modelMatrix = glm::mat4();
    viewMatrix = camera->GetWorldMatrix();

    aspectRatio = static_cast< float >( config->GraphicsConfig()->GetCurrentAspectRatio() );
    setClipPlanes( 0.01f, 100.0f );
    setFOV( 45.0f );
    projectionMatrix = getProjectionMatrix();

    glUseProgram( shaderId );
    glUniformMatrix4fv( modelMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( modelMatrix ) );
    glUniformMatrix4fv( viewMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( viewMatrix ) );
    glUniformMatrix4fv( projectionMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( projectionMatrix ) );

    // Back - Gray
    vertexData.push_back( glm::vec4( -0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 0.25f ) );
    
    vertexData.push_back( glm::vec4( -0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 0.25f ) );

    // Bottom - Purple
    vertexData.push_back( glm::vec4( -0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 0.25f ) );
    
    vertexData.push_back( glm::vec4(  0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 0.25f ) );

    // Front - Orange
    vertexData.push_back( glm::vec4( -0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 0.25f ) );
    
    vertexData.push_back( glm::vec4(  0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 0.25f ) );

    // Top - Green
    vertexData.push_back( glm::vec4( -0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 0.25f ) );
    
    vertexData.push_back( glm::vec4( -0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 0.25f ) );

    // Left - Red
    vertexData.push_back( glm::vec4( -0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 0.25f ) );
    
    vertexData.push_back( glm::vec4( -0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 0.25f ) );
    vertexData.push_back( glm::vec4( -0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 0.25f ) );

    // Right - Blue
    vertexData.push_back( glm::vec4(  0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 0.25f ) );
    
    vertexData.push_back( glm::vec4(  0.25f,  0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f,  0.25f, -0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.25f, -0.25f,  0.25f, 0.25f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 0.25f ) );

    initArrays();

    glClearColor( 0.2f, 0.4f, 0.45f, 1.0f );

    initialized = true;
}

void ChapterFour::Draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    shaderManager->SetActiveShaderByName( "basic" );

    glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 2 * sizeof( glm::vec4 ), 0 );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 2 * sizeof( glm::vec4 ), ( void * )sizeof( glm::vec4 ) );

    glDrawArrays( GL_TRIANGLES, 0, static_cast<GLsizei>(vertexData.size() / 2));

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glUseProgram( 0 );

    glFlush();
}

void ChapterFour::Step( float time_step )
{
    if( keyboard->IsKeydown( 'W' ) )
    {
        cameraVelocity.z += cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'S' ) )
    {
        cameraVelocity.z -= cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'D' ) )
    {
        cameraVelocity.x -= cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'A' ) )
    {
        cameraVelocity.x += cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'E' ) )
    {
        cameraVelocity.y += cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'Q' ) )
    {
        cameraVelocity.y -= cameraAcceleration * time_step;
    }

    glm::vec3 rotationAngles;
    if( keyboard->IsKeydown( 'J' ) )
    {
        rotationAngles.x += cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'L' ) )
    {
        rotationAngles.x -= cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'I' ) )
    {
        rotationAngles.y += cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'K' ) )
    {
        rotationAngles.y -= cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'O' ) )
    {
        rotationAngles.z += cameraAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'U' ) )
    {
        rotationAngles.z -= cameraAcceleration * time_step;
    }

    cameraVelocity += ( -cameraVelocity ) * cameraDrag * time_step;
    for( int i = 0; i < 3; i++ )
    {
        if( cameraVelocity[i] > 2.0f )
        {
            cameraVelocity[i] = 2.0f;
        }
        else if( cameraVelocity[i] < -2.0f )
        {
            cameraVelocity[i] = -2.0f;
        }
        else if( ( cameraVelocity[i] < 0.005f ) && ( cameraVelocity[i] > -0.005f ) )
        {
            cameraVelocity[i] = 0.0f;
        }
    }

    glm::vec3 newPosition = camera->GetPosition() + cameraVelocity * time_step;

    camera->SetPosition( newPosition );
    camera->SetRotation( rotationAngles );
    viewMatrix = camera->GetWorldMatrix();

    glUseProgram( shaderId );
    glUniformMatrix4fv( viewMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( viewMatrix ) );
}

void ChapterFour::Shutdown( void )
{
}

void ChapterFour::initArrays( void )
{
    glGenVertexArrays( 1, &vertexArrayObject );
    glBindVertexArray( vertexArrayObject );

    glGenBuffers( 1, &vertexBufferObject );
    glBindBuffer( GL_ARRAY_BUFFER, vertexBufferObject );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

}


void ChapterFour::setClipPlanes( float near_plane, float far_plane )
{
    nearClipPlane = near_plane;
    farClipPlane = far_plane;
}

void ChapterFour::setFOV( float new_fov )
{
    fov = new_fov;
}

glm::mat4 ChapterFour::getProjectionMatrix( void )
{
    glm::mat4 output;

    output = glm::perspective( fov, aspectRatio, nearClipPlane, farClipPlane );

    return output;
}

glm::mat4 ChapterFour::getViewMatrix( void )
{
    return viewMatrix;
}