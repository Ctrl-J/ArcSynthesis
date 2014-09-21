#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_four.h>
#include <ArcSynth/Config/config.h>
#include <ArcSynth/Config/chapter_data.h>
#include <ArcSynth/keyboard.h>
#include <ArcSynth/mouse.h>

ChapterFour::ChapterFour( const std::string &data_filename, std::shared_ptr<Configuration> config_ptr, 
                        std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Mouse> mouse_ptr,
                        std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
    camera = std::make_shared<FreeCamera>( logger_ptr );
    mouse = mouse_ptr;
    filename = data_filename;
}

ChapterFour::~ChapterFour()
{
    while( cubeOfCubes.size() > 0 )
    {
        if( cubeOfCubes.back() != nullptr )
        {
            delete cubeOfCubes.back();
            cubeOfCubes.back() = nullptr;
        }
        cubeOfCubes.pop_back();
    }
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

    cameraPositionAcceleration = 1.25f;
    cameraPositionDrag = 0.75f;
    
    cameraRotationAcceleration = 0.30f;
    cameraRotationDrag = 4.25f;

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
    glUniformMatrix4fv( viewMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( viewMatrix ) );
    glUniformMatrix4fv( projectionMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( projectionMatrix ) );

    for( int xIndex = 0; xIndex < 5; xIndex++ )
    {
        for( int yIndex = 0; yIndex < 5; yIndex++ )
        {
            for( int zIndex = 0; zIndex < 5; zIndex++ )
            {
                DemoCube *cube = new DemoCube( logger );
                cube->SetPosition( glm::vec3( 3 * xIndex, 3 * yIndex, 3 * zIndex ) );
                cube->Initialize();
                cubeOfCubes.push_back( cube );
            }
        }
    }

    glClearColor( 0.2f, 0.4f, 0.45f, 1.0f );

    initialized = true;
}

void ChapterFour::Draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    shaderManager->SetActiveShaderByName( "basic" );

    for( int cubeIndex = 0; cubeIndex < cubeOfCubes.size(); cubeIndex++ )
    {
        modelMatrix = cubeOfCubes[cubeIndex]->GetWorldMatrix();
        glUniformMatrix4fv( modelMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( modelMatrix ) );
        cubeOfCubes[cubeIndex]->Draw();
    }
    glUseProgram( 0 );

    glFlush();
}

void ChapterFour::Step( float time_step )
{
    if( keyboard->IsKeydown( 'W' ) )
    {
        cameraPositionVelocity.z += cameraPositionAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'S' ) )
    {
        cameraPositionVelocity.z -= cameraPositionAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'D' ) )
    {
        cameraPositionVelocity.x -= cameraPositionAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'A' ) )
    {
        cameraPositionVelocity.x += cameraPositionAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'E' ) )
    {
        cameraPositionVelocity.y += cameraPositionAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'Q' ) )
    {
        cameraPositionVelocity.y -= cameraPositionAcceleration * time_step;
    }

    glm::vec2 mouseDelta = mouse->GetMouseDelta();
    if( mouseDelta.x > 0.0f )
    {
        cameraRotationVelocity.x += cameraRotationAcceleration * time_step;
    }
    else if( mouseDelta.x < 0.0f )
    {
        cameraRotationVelocity.x -= cameraRotationAcceleration * time_step;
    }
    if( mouseDelta.y > 0.0f )
    {
        cameraRotationVelocity.y += cameraRotationAcceleration * time_step;
    }
    else if( mouseDelta.y < 0.0f )
    {
        cameraRotationVelocity.y -= cameraRotationAcceleration * time_step;
    }

    if( keyboard->IsKeydown( 'L' ) )
    {
        cameraRotationVelocity.x += cameraRotationAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'J' ) )
    {
        cameraRotationVelocity.x -= cameraRotationAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'I' ) )
    {
        cameraRotationVelocity.y += cameraRotationAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'K' ) )
    {
        cameraRotationVelocity.y -= cameraRotationAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'T' ) )
    {
        cameraRotationVelocity.z += cameraRotationAcceleration * time_step;
    }
    if( keyboard->IsKeydown( 'G' ) )
    {
        cameraRotationVelocity.z -= cameraRotationAcceleration * time_step;
    }

    cameraPositionVelocity -= ( cameraPositionVelocity ) * cameraPositionDrag * time_step;
    cameraRotationVelocity -= cameraRotationVelocity * cameraRotationDrag * time_step;

    for( int i = 0; i < 3; i++ )
    {
        if( cameraPositionVelocity[i] > 2.0f )
        {
            cameraPositionVelocity[i] = 2.0f;
        }
        else if( cameraPositionVelocity[i] < -2.0f )
        {
            cameraPositionVelocity[i] = -2.0f;
        }
        else if( glm::abs(cameraPositionVelocity[i]) < 0.00005f )
        {
            cameraPositionVelocity[i] = 0.0f;
        }
        
        if( cameraRotationVelocity[i] > 1.0f )
        {
            cameraRotationVelocity[i] = 1.0f;
        }
        else if( cameraRotationVelocity[i] < -1.0f )
        {
            cameraRotationVelocity[i] = -1.0f;
        }
        else if( glm::abs(cameraRotationVelocity[i]) < 0.00005f )
        {
            cameraRotationVelocity[i] = 0.0f;
        }
    }

    glm::vec3 newPosition = camera->GetPosition() + cameraPositionVelocity * time_step;

    camera->SetPosition( newPosition );
    camera->ApplyRotation( cameraRotationVelocity * time_step );
    viewMatrix = camera->GetWorldMatrix();

    glUseProgram( shaderId );
    glUniformMatrix4fv( viewMatrixUniformObject, 1, GL_FALSE, glm::value_ptr( viewMatrix ) );
}

void ChapterFour::Shutdown( void )
{
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