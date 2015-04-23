#include "RandFunc.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

RandFunc::RandFunc( const glm::vec3& focalPoint, float power, float distance )
    :
    Function( focalPoint, power, distance )
{
    srand( static_cast<unsigned>( time( NULL ) ) );
    m_seedation = rand() % 1000;
    std::cout << "seed: " << m_seedation << std::endl;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void RandFunc::apply( const glm::vec3& dirVect, glm::vec3& effect )
{
    // calculate the distance from the focal point
    float d = fabs( glm::distance( dirVect, m_focalPoint ) );
    if ( d <= m_currentDistance )
    {
        srand( static_cast<unsigned>( d * 10000  * m_seedation ) );
        float r = static_cast<float>( rand() % 1000 ) / 1000.0f;
        r = ( r * 2.0f ) - 1.0f;
        effect = dirVect *
                 r *
                 m_power *
                 ( ( m_currentDistance - d ) / m_currentDistance );
    }
}
