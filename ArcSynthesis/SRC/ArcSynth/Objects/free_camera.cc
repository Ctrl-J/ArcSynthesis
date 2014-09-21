#include <ArcSynth\precompiled.h>
#include <ArcSynth\Objects\free_camera.h>

FreeCamera::FreeCamera(std::shared_ptr<Logger> logger) : Model(logger)
{
}

FreeCamera::~FreeCamera()
{
}

bool FreeCamera::Initialize( void )
{
    position = glm::vec3( 0.0f, 0.0f, -50.0f );
    initialized = true;
    
    return true;
}

void FreeCamera::Shutdown( void )
{
}
