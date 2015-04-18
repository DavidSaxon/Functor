#include "SpotLight.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SpotLight::SpotLight(
        const std::string&    id,
              omi::Transform* transform,
              float           power,
        const glm::vec3&      colour,
              float           constantAtt,
              float           linearAtt,
              float           quadraticAtt,
              float           outerArc,
              float           innerArc )
    :
    Light         ( id, transform, power, colour ),
    m_constantAtt ( constantAtt ),
    m_linearAtt   ( linearAtt ),
    m_quadraticAtt( quadraticAtt ),
    m_outerArc    ( outerArc ),
    m_innerArc    ( innerArc )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

//-----------------------------------GETTERS------------------------------------

light::Type SpotLight::getLightType() const
{
    return light::SPOT;
}

float SpotLight::getConstantAtt() const
{
    return m_constantAtt;
}

float SpotLight::getLinearAtt() const
{
    return m_linearAtt;
}

float SpotLight::getQuadraticAtt() const
{
    return m_quadraticAtt;
}

float SpotLight::getOuterArc() const
{
    return m_outerArc;
}

float SpotLight::getInnerArc() const
{
    return m_innerArc;
}

//-----------------------------------SETTERS------------------------------------

void SpotLight::setConstantAtt( float constantAtt )
{
    m_constantAtt = constantAtt;
}

void SpotLight::setLinearAtt( float linearAtt )
{
    m_linearAtt = linearAtt;
}

void SpotLight::setQuadraticAtt( float quadraticAtt )
{
    m_quadraticAtt = quadraticAtt;
}

void SpotLight::setOuterArc( float outerArc )
{
    m_outerArc = outerArc;
}

void SpotLight::setInnerArc( float innerArc )
{
    m_innerArc = innerArc;
}

} // namespace omi
