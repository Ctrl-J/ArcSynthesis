#pragma once
#include <ArcSynth\precompiled.h>

class Logger;

//
//  All a model is, is an object that can be represented in space.
//  All objects in space have a position and an orientation.
//  For renderable/others use the derived class that has the additional functionality.
//
class Model
{
public:
    Model( std::shared_ptr<Logger> logger_ptr );
    virtual ~Model( void );
    Model( const Model &other ) = delete;
    Model &operator= ( const Model &other ) = delete;

    virtual bool Initialize( void ) = 0;
    virtual void Shutdown( void ) = 0;

    virtual void SetPosition( glm::vec3 new_position );
    virtual void SetOrientation( glm::fquat new_orientation );
    virtual void ApplyRotation( glm::vec3 new_rotation );

    virtual glm::vec3 GetPosition( void ) const;
    virtual glm::quat GetOrientation( void ) const;
    virtual glm::vec3 GetForwardVector( void ) const;
    virtual glm::vec3 GetUpVector( void ) const;
    virtual glm::vec3 GetRightVector( void ) const;
    virtual glm::mat4 GetWorldMatrix( void ) const;

    bool IsInitialized( void ) const;

protected:

    std::shared_ptr<Logger> logger;
    glm::vec3 position;
    glm::fquat orientation;

    bool initialized;
};
