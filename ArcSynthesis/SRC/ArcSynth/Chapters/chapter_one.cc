#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_one.h>
#include <ArcSynth/Config/chapter_data.h>

ChapterOne::ChapterOne( const std::string &data_filename, std::shared_ptr<Configuration> config_ptr, 
                        std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
    filename = data_filename;
}

ChapterOne::~ChapterOne()
{
}

void ChapterOne::Initialize( void )
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

    vertexData.push_back( 0.75f );
    vertexData.push_back( 0.75f );
    vertexData.push_back( 0.0f  );
    vertexData.push_back( 1.0f  );
    vertexData.push_back( 0.75f );
    vertexData.push_back(-0.75f );
    vertexData.push_back( 0.0f  );
    vertexData.push_back( 1.0f  );
    vertexData.push_back(-0.75f );
    vertexData.push_back(-0.75f );
    vertexData.push_back( 0.0f  );
    vertexData.push_back( 1.0f  );

    initArrays();

    glClearColor( 0.2f, 0.4f, 0.45f, 1.0f );

}

void ChapterOne::Draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    shaderManager->SetActiveShaderByName( "basic" );

    glBindBuffer( GL_ARRAY_BUFFER, position_buffer_object );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, 0 );

    glDrawArrays( GL_TRIANGLES, 0, static_cast< GLsizei >( vertexData.size() / 3 ) );

    glDisableVertexAttribArray( 0 );
    glUseProgram( 0 );

    glFlush();
}

void ChapterOne::Step( float time_step )
{
}

void ChapterOne::Shutdown( void )
{
}

void ChapterOne::initArrays( void )
{
    glGenBuffers( 1, &position_buffer_object );

    glBindBuffer( GL_ARRAY_BUFFER, position_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( float ) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glGenVertexArrays( 1, &vertex_array_object );
    glBindVertexArray( vertex_array_object );
}