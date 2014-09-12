#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_two.h>
#include <ArcSynth/Config/chapter_data.h>

ChapterTwo::ChapterTwo( const std::string &data_filename, std::shared_ptr<Configuration> config_ptr, 
                        std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
    filename = data_filename;
}

ChapterTwo::~ChapterTwo()
{
}

void ChapterTwo::Initialize( void )
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

    positionData.push_back( glm::vec4( -0.75f, -0.75f,  0.0f,  1.0f ) );
    positionData.push_back( glm::vec4(  0.75f,  -0.75f, 0.0f,  1.0f ) );
    positionData.push_back( glm::vec4(  0.0f,   0.75f,  0.0f,  1.0f ) );

    colorData.push_back( glm::vec4(  0.65f,  0.15f,  0.25f,  1.0f ) );
    colorData.push_back( glm::vec4(  0.15f,  0.25f,  0.65f,  1.0f ) );
    colorData.push_back( glm::vec4(  0.25f,  0.65f,  0.15f,  1.0f ) );

    initArrays();

    glClearColor( 0.2, 0.4, 0.45, 1.0 );

}

void ChapterTwo::Draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    shaderManager->SetActiveShaderByName( "basic" );

    glBindBuffer( GL_ARRAY_BUFFER, position_buffer_object );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glBindBuffer( GL_ARRAY_BUFFER, color_buffer_object );
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays( GL_TRIANGLES, 0, positionData.size());

    glDisableVertexAttribArray( 0 );
    glDisableVertexAttribArray( 1 );
    glUseProgram( 0 );

    glFlush();
}

void ChapterTwo::Step( double time_step )
{
}

void ChapterTwo::Shutdown( void )
{
}

void ChapterTwo::initArrays( void )
{
    glGenBuffers( 1, &position_buffer_object );
    glGenBuffers( 1, &color_buffer_object );

    glBindBuffer( GL_ARRAY_BUFFER, position_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * positionData.size(), &positionData[0], GL_STATIC_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, color_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * colorData.size(), &colorData[0], GL_STATIC_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glGenVertexArrays( 1, &vertex_array_object );
    glBindVertexArray( vertex_array_object );
}
