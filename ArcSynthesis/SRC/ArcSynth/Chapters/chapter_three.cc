#include <ArcSynth/precompiled.h>
#include <ArcSynth/Chapters/chapter_three.h>
#include <ArcSynth/Config/chapter_data.h>

ChapterThree::ChapterThree( const std::string &data_filename, std::shared_ptr<Configuration> config_ptr, 
                        std::shared_ptr<Keyboard> keyboard_ptr, std::shared_ptr<Logger> logger_ptr ) 
    : Chapter( config_ptr, keyboard_ptr, logger_ptr )
{
    filename = data_filename;
}

ChapterThree::~ChapterThree()
{
}

void ChapterThree::Initialize( void )
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

    positionSpeed = glm::vec3( 0.2f, 0.1f, 0.3f );
    colorSpeed.push_back( 0.25f );
    colorSpeed.push_back( 0.15f );
    colorSpeed.push_back( 0.05f );

    glClearColor( 0.2, 0.4, 0.45, 1.0 );

}

void ChapterThree::Draw( void )
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

void ChapterThree::Step( double time_step )
{
    positionData[0].x += time_step * positionSpeed[0];
    positionData[0].y += time_step * positionSpeed[0];

    if( positionData[0].x <= -1.0f )
    {
        positionData[0].x = -1.0f;
        positionData[0].y = -1.0f;
        positionSpeed[0] = ( -positionSpeed[0] );
    }
    else if( positionData[0].x >= 0 )
    {
        positionData[0].x = 0.0f;
        positionData[0].y = 0.0f;
        positionSpeed[0] = ( -positionSpeed[0] );
    }
    
    positionData[1].x += time_step * positionSpeed[1];
    positionData[1].y -= time_step * positionSpeed[1];

    if( positionData[1].x >= 1.0f )
    {
        positionData[1].x = 1.0f;
        positionData[1].y = -1.0f;
        positionSpeed[1] = ( -positionSpeed[1] );
    }
    else if( positionData[1].x <= 0.0f )
    {
        positionData[1].x = 0.0f;
        positionData[1].y = 0.0f;
        positionSpeed[1] = ( -positionSpeed[1] );
    }

    positionData[2].y += time_step * positionSpeed[2];
    if( positionData[2].y >= 1.0f )
    {
        positionData[2].y = 1.0f;
        positionSpeed[2] = ( -positionSpeed[2] );
    }
    else if( positionData[2].y <= 0.0f )
    {
        positionData[2].y = 0.0f;
        positionSpeed[2] = ( -positionSpeed[2] );
    }


    for( int colorIndex = 0; colorIndex < colorData.size(); colorIndex++ )
    {
        colorData[colorIndex].r += static_cast< float >( time_step ) * colorSpeed[colorIndex];
        colorData[colorIndex].g += static_cast< float >( time_step ) * colorSpeed[colorIndex];
        colorData[colorIndex].b += static_cast< float >( time_step ) * colorSpeed[colorIndex];
    
        if( colorData[colorIndex].r > 1.0f )
        {
            colorData[colorIndex].r = 1.0f;
        }
        else if( colorData[colorIndex].r <= 0.0f )
        {
            colorData[colorIndex].r = 0.0f;
        }
        
        if( colorData[colorIndex].g > 1.0f )
        {
            colorData[colorIndex].g = 1.0f;
        }
        else if( colorData[colorIndex].g <= 0.0f )
        {
            colorData[colorIndex].g = 0.0f;
        }
        
        if( colorData[colorIndex].b > 1.0f )
        {
            colorData[colorIndex].b = 1.0f;
        }
        else if( colorData[colorIndex].b <= 0.0f )
        {
            colorData[colorIndex].b = 0.0f;
        }
        
        float mag = glm::dot( colorData[colorIndex], colorData[colorIndex] );
        if( mag >= 4.0f )
    	{
    	    colorData[colorIndex].r = 1.0f;
    	    colorData[colorIndex].g = 1.0f;
    	    colorData[colorIndex].b = 1.0f;
    	    colorSpeed[colorIndex] = ( -colorSpeed[colorIndex] );
    	}
        else if( mag <= 1.003f )
        {
            colorData[colorIndex].r = 0.1f;
            colorData[colorIndex].g = 0.1f;
            colorData[colorIndex].b = 0.1f;
            colorSpeed[colorIndex] = ( -colorSpeed[colorIndex] );
        }
    }
    
    glBindBuffer( GL_ARRAY_BUFFER, position_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * positionData.size(), &positionData[0], GL_STREAM_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, color_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * colorData.size(), &colorData[0], GL_STREAM_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void ChapterThree::Shutdown( void )
{
}

void ChapterThree::initArrays( void )
{
    glGenBuffers( 1, &position_buffer_object );
    glGenBuffers( 1, &color_buffer_object );

    glBindBuffer( GL_ARRAY_BUFFER, position_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * positionData.size(), &positionData[0], GL_STREAM_DRAW );
    
    glBindBuffer( GL_ARRAY_BUFFER, color_buffer_object );
    glBufferData( GL_ARRAY_BUFFER, sizeof( glm::vec4 ) * colorData.size(), &colorData[0], GL_STREAM_DRAW );

    glBindBuffer( GL_ARRAY_BUFFER, 0 );

    glGenVertexArrays( 1, &vertex_array_object );
    glBindVertexArray( vertex_array_object );
}
