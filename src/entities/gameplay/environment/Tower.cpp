#include "Tower.hpp"

#include "src/data/Globals.hpp"
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

static const float WEAK_DISTANCE = 0.05f;
static const float MEDIUM_DISTANCE = 0.1f;
static const float STRONG_DISTANCE = 0.15f;
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
    m_height   ( height ),
    m_addHeight( 0.0f ),
    m_booming  ( false ),
    m_boomTimer( 0.0f )
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
            new omi::Specular( 64.0f, glm::vec3( 1.0f, 1.0f, 1.0f ) );
    if ( m_colour == tower::BLUE )
    {
        m_mesh1->getMaterial().colour = BLUE_COLOUR_1;
    }
    else
    {
        m_mesh1->getMaterial().colour = RED_COLOUR_1;
    }
    m_components.add( m_mesh1 );


    m_mesh2 = omi::ResourceManager::getMesh( "tower2", "", m_pos );
    m_mesh2->getMaterial().specular =
            new omi::Specular( 64.0f, glm::vec3( 1.0f, 1.0f, 1.0f ) );
    if ( m_colour == tower::BLUE )
    {
        m_mesh2->getMaterial().colour = BLUE_COLOUR_2;
    }
    else
    {
        m_mesh2->getMaterial().colour = RED_COLOUR_2;
    }
    m_mesh2->visible = false;
    if ( m_strength > tower::WEAK )
    {
        m_mesh2->visible = true;
    }
    m_components.add( m_mesh2 );


    m_mesh3 = omi::ResourceManager::getMesh( "tower3", "", m_pos );
    m_mesh3->getMaterial().specular =
            new omi::Specular( 64.0f, glm::vec3( 1.0f, 1.0f, 1.0f ) );
    if ( m_colour == tower::BLUE )
    {
        m_mesh3->getMaterial().colour = BLUE_COLOUR_3;
    }
    else
    {
        m_mesh3->getMaterial().colour = RED_COLOUR_3;
    }
    m_components.add( m_mesh3 );
    m_mesh3->visible = false;
    if ( m_strength > tower::NORMAL )
    {
        m_mesh3->visible = true;
    }

    m_boom = omi::ResourceManager::getMesh(
            "tower_explosion", "", m_pos );
    m_boom->getMaterial().glow =
            new omi::Glow( m_boom->getMaterial().colour.xyz(), 1.0f );
    m_boom->visible = false;
    m_components.add( m_boom );
}

void Tower::update()
{
    // skip if omicron is paused
    if ( global::pause )
    {
        return;
    }

    m_pos->translation.z = m_height + m_addHeight;

    if ( m_booming )
    {
        m_boomTimer += 0.04f * omi::fpsManager.getTimeScale();
        m_pos->scale.x = 1.0f * ( m_boomTimer * 5.0f );
        m_pos->scale.y = 1.0f * ( m_boomTimer * 5.0f );
        m_boom->getMaterial().glow =
                new omi::Glow( m_boom->getMaterial().colour.xyz(),
                1.0f - m_boomTimer
        );
        if ( m_boomTimer >= 1.0f )
        {
            remove();
        }
    }
}

void Tower::setHeight( float height )
{
    m_height = height;
}

void Tower::setAddHeight( float add )
{
    m_addHeight = add;
}

tower::Colour Tower::getColour() const
{
    return m_colour;
}

float Tower::getChangeDis() const
{
    switch( m_strength )
    {
        case tower::WEAK:
        {
            return WEAK_DISTANCE;
        }
        case tower::NORMAL:
        {
            return MEDIUM_DISTANCE;
        }
        default:
        {
            return STRONG_DISTANCE;
        }
    }
}

void Tower::destroy()
{
    m_mesh1->visible = false;
    m_mesh2->visible = false;
    m_mesh3->visible = false;

    m_booming = true;
    m_boomTimer = 0.0f;
    m_boom->visible = true;
}

void Tower::quickRemove()
{
    remove();
}
