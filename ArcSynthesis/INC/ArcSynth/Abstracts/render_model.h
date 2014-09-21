#pragma once
#include <ArcSynth\precompiled.h>
#include <ArcSynth\Abstracts\model.h>

class Logger;

//
//  All a model is, is an object that can be represented in space.
//  All objects in space have a position and an orientation.
//  For renderable/others use the derived class that has the additional functionality.
//
class RenderModel : public Model
{
public:
    RenderModel( std::shared_ptr<Logger> logger_ptr );
    virtual ~RenderModel( void );
    RenderModel( const RenderModel &other ) = delete;
    RenderModel &operator= ( const RenderModel &other ) = delete;

    virtual bool Initialize( void ) = 0;
    virtual void Draw( void ) = 0;
    virtual void Shutdown( void ) = 0;

    virtual void SetShaderName( const std::string &name );
    virtual std::string GetShaderName( void ) const;

protected:

    std::string shaderName;
};
