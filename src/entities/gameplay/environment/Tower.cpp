#include "Tower.hpp"

#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{
static const glm::vec4 BLUE_COLOUR_1( 0.3f, 0.3f, 1.0f, 1.0f );
static const glm::vec4 BLUE_COLOUR_2( 0.1f, 0.1f, 0.5f, 1.0f );
static const glm::vec4 BLUE_COLOUR_3( 0.3f, 0.3f, 0.7f, 1.0f );

static const glm::vec4 RED_COLOUR_1 ( 1.0f, 0.3f, 0.3f, 1.0f );
static const glm::vec4 RED_COLOUR_2 ( 0.5f, 0.1f, 0.1f, 1.0f );
static const glm::vec4 RED_COLOUR_3 ( 0.7f, 0.3f, 0.3f, 1.0f );
} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Tower::Tower(
        omi::Transform* parentPos,
        tower::Colour colour,
        tower::Strength strength,
        float height )
    :
    m_parentPos( parentPos ),
    m_colour   ( colour ),
    m_strength ( strength ),
    m_height   ( height )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Tower::init()
{
    m_pos = new omi::Transform(
            "",
            m_parentPos,
            glm::vec3( 0.0f, 0.0f, m_height ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_pos );

    m_mesh1 = omi::ResourceManager::getMesh( "tower1", "", m_pos );
    m_mesh1->getMaterial().specular =
            new omi::Specular( 64.0f, glm::vec3( 0.5f, 0.5f, 0.5f ) );
    if ( m_colour == tower::BLUE )
    {
        m_mesh1->getMaterial().colour = BLUE_COLOUR_1;
    }
    else
    {
        m_mesh1->getMaterial().colour = RED_COLOUR_1;
    }
    m_components.add( m_mesh1 );

    if ( m_strength > tower::WEAK )
    {
        m_mesh2 = omi::ResourceManager::getMesh( "tower2", "", m_pos );
        m_mesh2->getMaterial().specular =
                new omi::Specular( 64.0f, glm::vec3( 0.5f, 0.5f, 0.5f ) );
        if ( m_colour == tower::BLUE )
        {
            m_mesh2->getMaterial().colour = BLUE_COLOUR_2;
        }
        else
        {
            m_mesh2->getMaterial().colour = RED_COLOUR_2;
        }
        m_components.add( m_mesh2 );
    }

    if ( m_strength > tower::NORMAL )
    {
        m_mesh3 = omi::ResourceManager::getMesh( "tower3", "", m_pos );
        m_mesh3->getMaterial().specular =
                new omi::Specular( 64.0f, glm::vec3( 0.5f, 0.5f, 0.5f ) );
        if ( m_colour == tower::BLUE )
        {
            m_mesh3->getMaterial().colour = BLUE_COLOUR_3;
        }
        else
        {
            m_mesh3->getMaterial().colour = RED_COLOUR_3;
        }
        m_components.add( m_mesh3 );
    }
}

void Tower::update()
{
    m_pos->translation.z = m_height;
}

void Tower::setHeight( float height )
{
    m_height = height;
}

tower::Colour Tower::getColour() const
{
    return m_colour;
}
