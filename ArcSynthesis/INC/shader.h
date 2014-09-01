#pragma once
#include <precompiled.h>

class Logger;

class Shader
{
public:
    Shader( std::shared_ptr<Logger> log_ptr );
    bool Initialize( const std::string &name,
                     const std::string &vertex_shader_code,
                     const std::string &fragment_shader_code );

    GLuint GetProgramId( void ) const;
    std::string GetShaderName( void ) const;

    std::string GetVertexShaderCode( void ) const;
    std::string GetFragmentShaderCode( void ) const;

    bool IsLinked( void ) const;

private:
    std::string shaderName;
    std::string vertexShaderCode;
    std::string fragmentShaderCode;
    GLuint shaderProgramId;
    bool isLinked;

    std::string getShaderError( GLuint identifier );
    std::string getProgramError( GLuint identifier );

    std::shared_ptr<Logger> logger;
};
