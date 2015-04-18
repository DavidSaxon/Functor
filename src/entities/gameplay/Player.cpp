#include "Player.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/environment/World.hpp"
#include "src/omicron/input/Input.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

// the base speed at which the camera zooms at
static const float ZOOM_BASE_SPEED = 0.035f;
// the zoom clamp when in planet select
static const float ZOOM_CLAMP_NEAR_PS = 20.0f;
static const float ZOOM_CLAMP_FAR_PS  = 160.0f;
// the zoom clamp when in planet orbit
static const float ZOOM_CLAMP_NEAR_PO = 2.0f;
static const float ZOOM_CLAMP_FAR_PO  = 7.0f;
// the base speed which the camera rotates at
static const float LOOK_BASE_SPEED = 0.035f;

} // namespace anonymous


//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Player::Player( const std::vector<World*>& worlds )
    :
    m_state ( gameplay::PLANET_SELECT ),
    m_worlds( worlds ),
    m_world ( NULL )
{
    global::m_inOrbit = false;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Player::init()
{
    initComponents();
}

void Player::update()
{
    // skip if omicron is paused
    if ( global::pause )
    {
        return;
    }

    // don't use input if omicron doesn't have focus
    if ( omi::omi_hasFocus )
    {
        look();
    }

    // run logic based on state
    switch ( m_state )
    {
        case gameplay::PLANET_SELECT:
        {
            planetSelect();
            break;
        }
        case gameplay::PLANET_ORBIT:
        {
            // TODO:
            break;
        }
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Player::look()
{
    // zoom based on scrolling
    m_camPos->translation.z -=
            omi::input::getMouseScroll() *
            ZOOM_BASE_SPEED *
            m_camPos->translation.z;

    // clamp zoom
    if ( m_state == gameplay::PLANET_SELECT )
    {
        m_camPos->translation.z = util::math::clamp<float>(
                m_camPos->translation.z,
                ZOOM_CLAMP_NEAR_PS,
                ZOOM_CLAMP_FAR_PS
        );
    }
    else if ( m_state == gameplay::PLANET_ORBIT )
    {
        m_camPos->translation.z = util::math::clamp<float>(
                m_camPos->translation.z,
                ZOOM_CLAMP_NEAR_PO,
                ZOOM_CLAMP_FAR_PO
        );
    }

    if ( !omi::input::mousePressed( omi::input::mouse_button::LEFT ) )
    {
        return;
    }

    // rotate the camera based on how far the mouse has moved
    m_camFocus->rotation.x +=
        ( omi::displaySettings.getCentre().y - omi::input::getMousePos().y ) *
        LOOK_BASE_SPEED * global::lookSensitivity;
    m_camFocus->rotation.y +=
        ( omi::displaySettings.getCentre().x - omi::input::getMousePos().x ) *
        LOOK_BASE_SPEED * global::lookSensitivity;
}

void Player::planetSelect()
{
    int index = -1;

    if ( omi::input::isKeyPressed( omi::input::key::NUM_1 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_1 ) )
    {
        index = 0;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_2 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_2 ) )
    {
        index = 1;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_3 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_3 ) )
    {
        index = 2;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_4 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_4 ) )
    {
        index = 3;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_5 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_5 ) )
    {
        index = 4;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_6 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_6 ) )
    {
        index = 5;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_7 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_7 ) )
    {
        index = 6;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_8 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_8 ) )
    {
        index = 7;
    }
    else if ( omi::input::isKeyPressed( omi::input::key::NUM_9 ) ||
         omi::input::isKeyPressed( omi::input::key::NUMPAD_9 ) )
    {
        index = 8;
    }

    // valid index?
    if ( index >= 0 && static_cast<unsigned>( index ) < m_worlds.size() )
    {
        // select the world
        m_state = gameplay::PLANET_ORBIT; // TODO: transition state
        m_world = m_worlds[ index ];

        // parent to planet position
        m_camFocus->parent = m_world->getPosition();

        // we're in orbit
        global::m_inOrbit = true;
    }
}

void Player::initComponents()
{
    // transformations
    m_camFocus = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3( -90.0f, 0.0f, 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_camFocus );
    m_camPos = new omi::Transform(
            "",
            m_camFocus,
            glm::vec3( 0.0f, 0.0f, 90.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_camPos );

    // camera
    omi::Camera* camera =
            new omi::Camera( "", omi::cam::PERSPECTIVE, m_camPos, 50.0f );
    camera->setExposure( 1.2f );
    m_components.add( camera );
}
