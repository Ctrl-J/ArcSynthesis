#include <ArcSynth\precompiled.h>
#include <ArcSynth\Abstracts\model.h>
#include <ArcSynth\logger.h>

Model::Model( std::shared_ptr<Logger> set_logger )
{
    logger = set_logger;

    initialized = false;

    position = glm::vec3( 0, 0, 0 );
    orientation = glm::quat( 1, 0, 0, 0 );

}

Model::~Model( void )
{
}

void Model::SetPosition( glm::vec3 new_position )
{
    position = new_position;
}

glm::vec3 Model::GetPosition( void ) const
{
    return position;
}

glm::quat Model::GetOrientation( void ) const
{
    return orientation;
}

// Applies rotation to forward (x), up (y), and right (z) axes
void Model::SetRotation( glm::vec3 new_rotation )
{
    float xx = orientation.x * orientation.x;
    float xy = orientation.x * orientation.y;
    float xz = orientation.x * orientation.z;
    float xw = orientation.x * orientation.w;
    
    float yy = orientation.y * orientation.y;
    float yz = orientation.y * orientation.z;
    float yw = orientation.y * orientation.w;

    float zz = orientation.y * orientation.z;
    float zw = orientation.y * orientation.w;

    bool forwardRotate = false;
    bool upRotate = false;
    bool rightRotate = false;

    glm::fquat forward_rotation;
    if( glm::abs( new_rotation.z ) > glm::epsilon<float>() )
    {
        float sin_forward_angle = glm::sin( new_rotation.z / 2.0f );
        float cos_forward_angle = glm::cos( new_rotation.z / 2.0f );
        glm::vec3 forward = glm::normalize( glm::vec3( 2 * ( xz + yw ),
                                                       2 * ( xy - xw ),
                                                       1 - ( 2 * ( xx + yy ) ) ) );

        forward_rotation.x = forward.x * sin_forward_angle;
        forward_rotation.y = forward.y * sin_forward_angle;
        forward_rotation.z = forward.z * sin_forward_angle;
        forward_rotation.w = cos_forward_angle;

        forwardRotate = true;
    }

    glm::fquat up_rotation;
    if( glm::abs( new_rotation.x ) > glm::epsilon<float>() )
    {
        float sin_up_angle = glm::sin( new_rotation.x / 2.0f );
        float cos_up_angle = glm::cos( new_rotation.x / 2.0f );

        glm::vec3 up = glm::normalize( glm::vec3( 2 * ( xy - zw ),
                                                  1 - 2 * ( xx - zz ),
                                                  2 * ( yz + xw ) ) );

        up_rotation.x = up.x * sin_up_angle;
        up_rotation.y = up.y * sin_up_angle;
        up_rotation.z = up.z * sin_up_angle;
        up_rotation.w = cos_up_angle;

        upRotate = true;
    }

    glm::fquat right_rotation;
    if( glm::abs( new_rotation.y ) > glm::epsilon<float>() )
    {
        float sin_right_angle = glm::sin( new_rotation.y / 2.0f );
        float cos_right_angle = glm::cos( new_rotation.y / 2.0f );

        glm::vec3 right = glm::normalize( glm::vec3( 1 - 2 * ( yy + zz ),
                                                     2 * ( xy - zw ),
                                                     2 * ( xz - yw ) ) );
        
        right_rotation.x = right.x * sin_right_angle;
        right_rotation.y = right.y * sin_right_angle;
        right_rotation.z = right.z * sin_right_angle;
        right_rotation.w = cos_right_angle;

        rightRotate = true;
    }

    glm::fquat rotation = orientation;
    if( forwardRotate )
    {
        rotation = forward_rotation * rotation;
    }
    
    if( rightRotate )
    {
        rotation = right_rotation * rotation;
    }

    if( upRotate )
    {
        rotation = up_rotation * rotation;
    }


    orientation = rotation;
}

glm::vec3 Model::GetForwardVector( void ) const
{
    float xx = orientation.x * orientation.x;
    float xy = orientation.x * orientation.y;
    float xz = orientation.x * orientation.z;
    float xw = orientation.x * orientation.w;
    
    float yy = orientation.y * orientation.y;
    float yz = orientation.y * orientation.z;
    float yw = orientation.y * orientation.w;

    float zz = orientation.y * orientation.z;
    float zw = orientation.y * orientation.w;

    return glm::vec3( 2 * ( xz + yw ),
                      2 * ( xy - xw ),
                      1 - ( 2 * ( xx + yy ) ) );
}

glm::vec3 Model::GetUpVector( void ) const
{
    float xy = orientation.x * orientation.y;
    float xx = orientation.x * orientation.x;
    float xw = orientation.x * orientation.w;
    
    float yz = orientation.y * orientation.z;

    float zz = orientation.y * orientation.z;
    float zw = orientation.y * orientation.w;

    return glm::vec3( 2 * ( xy - zw ),
                      1 - 2 * ( xx - zz ),
                      2 * ( yz + xw ) );
}

glm::vec3 Model::GetRightVector( void ) const
{
    float xy = orientation.x * orientation.y;
    float xz = orientation.x * orientation.z;
    
    float yy = orientation.y * orientation.y;
    float yw = orientation.y * orientation.w;

    float zz = orientation.y * orientation.z;
    float zw = orientation.y * orientation.w;

    return glm::vec3( 1 - 2 * ( yy + zz ),
                      2 * ( xy - zw ),
                      2 * ( xz - yw ) );
}

glm::mat4 Model::GetWorldMatrix( void ) const
{
    glm::mat4 output;

    output = glm::mat4_cast( orientation );

    output = output * glm::translate( output, position );

    return output;
}

bool Model::IsInitialized( void ) const
{
    return initialized;
}