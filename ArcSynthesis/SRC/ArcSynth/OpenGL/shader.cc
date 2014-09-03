#include <ArcSynth/precompiled.h>
#include <ArcSynth/OpenGL/shader.h>
#include <ArcSynth/logger.h>

Shader::Shader( std::shared_ptr<Logger> log_ptr )
{
    logger = log_ptr;
    shaderProgramId = -1;
    isLinked = false;
}

bool Shader::Initialize( const std::string &name,
                         const std::string &vertex_shader_code,
                         const std::string &fragment_shader_code )
{
    shaderName = name;
    vertexShaderCode = vertex_shader_code;
    fragmentShaderCode = fragment_shader_code;

    shaderProgramId = glCreateProgram();
    
    GLuint vertex_shader_id = glCreateShader( GL_VERTEX_SHADER );
    const GLchar *vertex_shader_source = vertexShaderCode.c_str();
    glShaderSource( vertex_shader_id, 1, &vertex_shader_source, NULL );
    glCompileShader( vertex_shader_id );

    GLint compiled;
    glGetShaderIV( vertex_shader_id, GL_COMPILE_STATUS, &compiled );
    if( compiled == GL_FALSE )
    {
        std::string message = getShaderError( vertex_shader_id );
        logger->Log( LOG_TYPE::ERR, "Vertex shader compile error", message );
        return false;
    }
    
    glAttachShader( shaderProgramId, vertex_shader_id );
    
    GLuint fragment_shader_id = glCreateShader( GL_FRAGMENT_SHADER );
    const GLchar *fragment_shader_source = fragmentShaderCode.c_str();
    glShaderSource( fragment_shader_id, 1, &fragment_shader_source, NULL );
    glCompileShader( fragment_shader_id );

    compiled = GL_FALSE;
    glGetShaderIV( fragment_shader_id, GL_COMPILE_STATUS, &compiled );
    if( compiled == GL_FALSE )
    {
        std::string message = getShaderError( fragment_shader_id );
        logger->Log( LOG_TYPE::ERR, "Fragment shader compile error", message );
        return false;
    }

    glAttachShader( shaderProgramId, fragment_shader_id );

    glLinkProgram( shaderProgramId );

    GLint linked;
    glGetProgramIV( shaderProgramId, GL_LINK_STATUS, &linked );
    if( linked == GL_FALSE )
    {
        std::string message = getProgramError( shaderProgramId );
        logger->Log( LOG_TYPE::ERR, "Shader link error", message );
        return false;
    }

    glDeleteShader( vertex_shader_id );
    glDeleteShader( fragment_shader_id );

    isLinked = true;
    return true;
}

GLuint Shader::GetProgramId( void ) const
{
    if( isLinked == true )
    {
        return shaderProgramId;
    }

    return -1;
}

std::string Shader::GetShaderName( void ) const
{
    return shaderName;
}

std::string Shader::GetVertexShaderCode( void ) const
{
    return vertexShaderCode;
}

std::string Shader::GetFragmentShaderCode( void ) const
{
    return fragmentShaderCode;
}

bool Shader::IsLinked( void ) const
{
    return isLinked;
}

std::string Shader::getShaderError( GLuint identifier )
{
    std::string output;
    GLsizei length;
    std::vector<char> info_log;
    glGetShaderIV( identifier, GL_INFO_LOG_LENGTH, &length );

    if( length <= 0 )
    {
        logger->Log( LOG_TYPE::ERR, "Error reading shader info log", "Info log reported as having zero length." );
        return output;
    }
    else
    {
        info_log.resize( length + 1, ' ' );
    }

    glGetShaderInfoLog( identifier, GL_INFO_LOG_LENGTH, &length, &info_log[0] );

    output = std::string( info_log.begin(), info_log.end() );

    return output;
}

std::string Shader::getProgramError( GLuint identifier )
{
    std::string output;
    GLsizei length;
    std::vector<char> info_log;
    glGetProgramIV( identifier, GL_INFO_LOG_LENGTH, &length );

    if( length <= 0 )
    {
        logger->Log( LOG_TYPE::ERR, "Error reading shader info log", "Info log reported as having zero length." );
        return output;
    }
    else
    {
        info_log.resize( length + 1, ' ' );
    }

    glGetProgramInfoLog( identifier, GL_INFO_LOG_LENGTH, &length, &info_log[0] );

    output = std::string( info_log.begin(), info_log.end() );

    return output;
}
