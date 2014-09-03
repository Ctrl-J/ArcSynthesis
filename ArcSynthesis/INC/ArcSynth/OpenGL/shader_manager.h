#pragma once
#include <ArcSynth/precompiled.h>
#include <ArcSynth/OpenGL/shader.h>
#include <ArcSynth/logger.h>

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