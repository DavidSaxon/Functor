#include "TanFunc.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TanFunc::TanFunc( const glm::vec3& focalPoint, float power, float distance )
    :
    Function( focalPoint, power, distance )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TanFunc::apply( const glm::vec3& dirVect, glm::vec3& effect )
{
    // calculate the distance from the focal point
    float d = fabs( glm::distance( dirVect, m_focalPoint ) );
    if ( d <= m_currentDistance )
    {
        effect = dirVect *
                 util::math::clamp(
                        static_cast<float>( tan( d * 7.0f ) ), -1.0f, 1.0f ) *
                 m_power * 0.5f *
                 ( ( m_currentDistance - d ) / m_currentDistance );
    }
}
