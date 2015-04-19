#include "Function.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Function::Function( const glm::vec3& focalPoint, float power, float distance )
    :
    m_focalPoint     ( focalPoint ),
    m_power          ( power ),
    m_currentDistance( distance ),
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
    // TODO: increase distance
}
