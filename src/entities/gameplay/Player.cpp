#include "Player.hpp"

#include "src/data/Globals.hpp"
#include "src/omicron/input/Input.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{

// the base speed at which the camera zooms at
static const float ZOOM_BASE_SPEED = 0.035f;
// the base speed which the camera rotates at
static const float LOOK_BASE_SPEED = 0.035f;

} // namespace anonymous


//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Player::Player()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Player::init()
{
    // TODO: REMOVE ME
    omi::Transform* dir = new omi::Transform(
                "",
                glm::vec3( -1.0f, 0.5f, 0.0f ),
                glm::vec3(),
                glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( dir );
    omi::DirectionalLight* light = new omi::DirectionalLight(
            "", dir, 1.0f, glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( light );


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

void Player::initComponents()
{
    // transformations
    m_camFocus = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_camFocus );
    m_camPos = new omi::Transform(
            "",
            m_camFocus,
            glm::vec3( 0.0f, 0.0f, 3.0f ),
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
