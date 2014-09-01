#include <precompiled.h>
#include <shader_manager.h>

ShaderManager::ShaderManager( std::shared_ptr<Logger> logger_ptr )
{
    logger = logger_ptr;
}

bool ShaderManager::LoadShader( const Shader &target )
{
    if( target.IsLinked() == false )
    {
        return false;
    }

    shaderSet.insert( std::make_pair( target.GetShaderName(), target ) );

    return true;
}

GLuint ShaderManager::GetShaderByName( const std::string &name ) const
{
    std::map<std::string, Shader>::const_iterator shader = shaderSet.find( name );
    if( shader == shaderSet.end() )
    {
        logger->Log( LOG_TYPE::ERR, "Invalid Shader", "Shader " + name + " does not appear to be loaded." );
        return -1;
    }

    return shader->second.GetProgramId();
}

bool ShaderManager::SetActiveShaderByName( const std::string &name ) const
{
    GLuint shaderId = GetShaderByName( name );
    if( shaderId != -1 )
    {
        glUseProgram( shaderId );
        return true;
    }

    logger->Log( LOG_TYPE::ERR, "Invalid Shader", "Tried to activate an invalid shader id." );
    return false;
}

