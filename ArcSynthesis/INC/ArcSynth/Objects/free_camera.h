#pragma once
#include <ArcSynth\precompiled.h>
#include <ArcSynth\Abstracts\model.h>

class FreeCamera : public Model
{
public:
    FreeCamera( std::shared_ptr<Logger> logger);
    ~FreeCamera();

    void Initialize( void );
    void Shutdown( void );

private:
};

