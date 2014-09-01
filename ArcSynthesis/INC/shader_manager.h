#pragma once
#include <precompiled.h>
#include <shader.h>
#include <logger.h>

class ShaderManager
{
public:
    ShaderManager( std::shared_ptr<Logger> logger_ptr );

    bool LoadShader( const Shader &target );

    GLuint GetShaderByName( const std::string &name ) const;
    bool SetActiveShaderByName( const std::string &name ) const;

private:
    std::map<std::string, Shader> shaderSet;

    std::shared_ptr<Logger> logger;
};