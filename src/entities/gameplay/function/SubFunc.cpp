#include "SubFunc.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SubFunc::SubFunc( const glm::vec3& focalPoint, float power, float distance )
    :
    Function( focalPoint, power, distance )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void SubFunc::apply( const glm::vec3& dirVect, glm::vec3& effect )
{
    // calculate the distance from the focal point
    float d = fabs( glm::distance( dirVect, m_focalPoint ) );
    if ( d <= m_currentDistance / 2.0f )
    {
        effect = dirVect * -m_power;
    }
}
