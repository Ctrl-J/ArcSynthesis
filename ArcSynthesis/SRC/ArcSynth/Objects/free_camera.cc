#include <ArcSynth\precompiled.h>
#include <ArcSynth\Objects\free_camera.h>

FreeCamera::FreeCamera(std::shared_ptr<Logger> logger) : Model(logger)
{
}

FreeCamera::~FreeCamera()
{
}

void FreeCamera::Initialize( void )
{
    position = glm::vec3( 0.0f, 0.0f, -5.0f );
    initialized = true;
}

void FreeCamera::Shutdown( void )
{
}
