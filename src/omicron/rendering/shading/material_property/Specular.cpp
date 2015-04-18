#include "Specular.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Specular::Specular( float shininess, const glm::vec3& colour, Texture* map )
    :
    m_shininess( shininess ),
    m_colour   ( colour ),
    m_map      ( map )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

//-----------------------------------GETTERS------------------------------------

float Specular::getShininess() const
{
    return m_shininess;
}

const glm::vec3& Specular::getColour() const
{
    return m_colour;
}

const Texture* Specular::getMap() const
{
    return m_map;
}

//-----------------------------------SETTERS------------------------------------

void Specular::setShininess( float shininess )
{
    m_shininess = shininess;
}

void Specular::setColour( const glm::vec3& colour )
{
    m_colour = colour;
}

void Specular::setMap( const Texture* map )
{
    m_map = map;
}

} // namespace omi
