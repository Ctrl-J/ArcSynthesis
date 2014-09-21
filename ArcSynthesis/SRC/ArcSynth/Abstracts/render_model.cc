#include <ArcSynth\precompiled.h>
#include <ArcSynth\Abstracts\render_model.h>

RenderModel::RenderModel( std::shared_ptr<Logger> logger ) : Model( logger )
{
}

RenderModel::~RenderModel( void )
{
}

void RenderModel::SetShaderName( const std::string &name )
{
    shaderName = name;
}

std::string RenderModel::GetShaderName( void ) const
{
    return shaderName;
}

