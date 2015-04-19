#include "Function.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Function::Function( const glm::vec3& focalPoint, float power, float distance )
    :
    m_focalPoint     ( focalPoint ),
    m_power          ( power ),
    m_currentDistance( 0.0f ),
    m_maxDistance    ( distance )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Function::init()
{
}

void Function::update()
{
    if ( m_currentDistance < m_maxDistance )
    {
        m_currentDistance += 0.02f * omi::fpsManager.getTimeScale();
    }
    else
    {
        m_currentDistance = m_maxDistance;
    }
}
