#include <precompiled.h>
#include <chapter_one.h>
#include <chapter_data.h>

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
    color = glm::vec3( 0.2, 0.4, 0.45 );
    glClearColor( color.r, color.g, color.b, 1.0 );

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
}

void ChapterOne::Draw( void )
{
}

void ChapterOne::Step( double time_step )
{
}

void ChapterOne::Shutdown( void )
{
}
