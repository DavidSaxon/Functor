#include "Glow.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Glow::Glow( const glm::vec3& colour, float brightness, Texture* texture ) :
    m_colour    ( colour ),
    m_brightness( brightness ),
    m_texture   ( texture )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

//-----------------------------------GETTERS------------------------------------

const glm::vec3& Glow::getColour() const
{
    return m_colour;
}

float Glow::getBrightness() const
{
    return m_brightness;
}

Texture* Glow::getTexture()
{
    return m_texture;
}

//-----------------------------------SETTERS------------------------------------

void Glow::setColour( const glm::vec3& colour )
{
    m_colour = colour;
}

void Glow::setBrightness( float brightness )
{
    m_brightness = brightness;
}

void Glow::setTexture( Texture* texture )
{
    m_texture = texture;
}

} // namespace omi
