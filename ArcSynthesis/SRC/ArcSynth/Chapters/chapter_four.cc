#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_four.h>
#include <ArcSynth/Config/chapter_data.h>

ChapterFour::ChapterFour( const std::string &data_filename, std::shared_ptr<Configuration> config_ptr, 
                        std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
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

    // Back - Gray
    vertexData.push_back( glm::vec4( -1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 1.00f ) );
    
    vertexData.push_back( glm::vec4( -1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.50f,  0.50f,  0.50f, 1.00f ) );

    // Bottom - Purple
    vertexData.push_back( glm::vec4( -1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 1.00f ) );
    
    vertexData.push_back( glm::vec4(  1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.62f,  0.36f,  0.65f, 1.00f ) );

    // Front - Orange
    vertexData.push_back( glm::vec4( -1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 1.00f ) );
    
    vertexData.push_back( glm::vec4(  1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.97f,  0.57f,  0.12f, 1.00f ) );

    // Top - Green
    vertexData.push_back( glm::vec4( -1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 1.00f ) );
    
    vertexData.push_back( glm::vec4( -1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.71f,  0.83f,  0.20f, 1.00f ) );

    // Left - Red
    vertexData.push_back( glm::vec4( -1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 1.00f ) );
    
    vertexData.push_back( glm::vec4( -1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 1.00f ) );
    vertexData.push_back( glm::vec4( -1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.69f,  0.11f,  0.24f, 1.00f ) );

    // Right - Blue
    vertexData.push_back( glm::vec4(  1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 1.00f ) );
    
    vertexData.push_back( glm::vec4(  1.00f,  1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f,  1.00f, -1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 1.00f ) );
    vertexData.push_back( glm::vec4(  1.00f, -1.00f,  1.00f, 1.00f ) );
    vertexData.push_back( glm::vec4(  0.00f,  0.67f,  0.92f, 1.00f ) );

    initArrays();

    glClearColor( 0.2f, 0.4f, 0.45f, 1.0f );

    initialized = true;
}

void ChapterFour::Draw( void )
{
    glClear( GL_COLOR_BUFFER_BIT );
    shaderManager->SetActiveShaderByName( "basic" );

    glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer_object );
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
}

void ChapterFour::Shutdown( void )
{
}

void ChapterFour::initArrays( void )
{
    glGenVertexArrays( 1, &vertex_array_object );
    glBindVertexArray( vertex_array_object );

    glGenBuffers( 1, &vertex_buffer_object );
    glBindBuffer( GL_ARRAY_BUFFER, vertex_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );

}
