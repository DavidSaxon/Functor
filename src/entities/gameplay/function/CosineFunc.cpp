#include "CosineFunc.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

CosineFunc::CosineFunc( const glm::vec3& focalPoint, float power, float distance )
    :
    Function( focalPoint, power, distance )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void CosineFunc::apply( const glm::vec3& dirVect, glm::vec3& effect )
{
    // calculate the distance from the focal point
    float d = fabs( glm::distance( dirVect, m_focalPoint ) );
    if ( d <= m_currentDistance )
    {
        effect = dirVect *
                 static_cast<float>( cos( d * 30.0f ) ) *
                 m_power *
                 ( ( m_currentDistance - d ) / m_currentDistance );
    }
}
