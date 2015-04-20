#include "DestroyFunc.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

DestroyFunc::DestroyFunc( const glm::vec3& focalPoint, float power, float distance )
    :
    Function( focalPoint, power, distance ),
    m_time  ( 0.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void DestroyFunc::update()
{
    m_time += 0.001f * omi::fpsManager.getTimeScale();
}

bool DestroyFunc::isDone()
{
    return false;
}

void DestroyFunc::apply( const glm::vec3& dirVect, glm::vec3& effect )
{
    // calculate the distance from the focal point
    float d = fabs( glm::distance( dirVect, m_focalPoint ) );
    effect = dirVect *
             static_cast<float>( sin( ( d + m_time ) * 30.0f ) ) * 0.04f;
}
