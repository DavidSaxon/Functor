#include "Player.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/Gui.hpp"
#include "src/entities/gameplay/environment/World.hpp"
#include "src/entities/gameplay/function/FunctionAttack.hpp"
#include "src/entities/gameplay/function/LowerFunc.hpp"
#include "src/entities/gameplay/function/RaiseFunc.hpp"
#include "src/entities/gameplay/function/SineFunc.hpp"
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
// default zoom level for planet orbit
static const float ZOOM_DEFAULT_PO    = 4.0f;


// the base speed which the camera rotates at
static const float LOOK_BASE_SPEED = 0.035f;

// transition speeds
static const float TRANS_ZOOM_SPEED = 2.0f;
static const float TRANS_MOVE_SPEED = 2.0f;
static const float TRANS_TILT_SPEED = 2.0f;

// regeneration time
static const float REGEN_SPEED = 0.01f;

} // namespace anonymous


//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Player::Player( Gui* gui, const std::vector<World*>& worlds )
    :
    m_state          ( gameplay::PLANET_SELECT ),
    m_gui            ( gui ),
    m_worlds         ( worlds ),
    m_world          ( NULL ),
    m_generatingFuncs( 2.0f )
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
        // hide the gui
        m_gui->setVisible( false );
        return;
    }
    else if ( m_state == gameplay::PLANET_ORBIT )
    {
        // show gui
        m_gui->setVisible( true );
    }

    // don't use input if omicron doesn't have focus
    if ( omi::omi_hasFocus &&
         m_state == gameplay::PLANET_SELECT ||
         m_state == gameplay::PLANET_ORBIT )
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
        case gameplay::TRANS_TO_PLANET:
        {
            transToPlanet();
            break;
        }
        case gameplay::PLANET_ORBIT:
        {
            planetOrbit();
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

    // rotate the camera based on how far the mouse has moved
    m_camFocus->rotation.x +=
        ( omi::displaySettings.getCentre().y - omi::input::getMousePos().y ) *
        LOOK_BASE_SPEED * global::lookSensitivity;
    m_camFocus->rotation.y +=
        ( omi::displaySettings.getCentre().x - omi::input::getMousePos().x ) *
        LOOK_BASE_SPEED * global::lookSensitivity;

    m_camFocus->rotation.x = util::math::clamp(
            m_camFocus->rotation.x, -90.0f, 90.0f );
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
        m_state = gameplay::TRANS_TO_PLANET;
        m_world = m_worlds[ index ];

        // parent to planet position
        m_distT->parent = m_world->getRotPoint();

        // we're in orbit
        global::m_inOrbit = true;
    }
}

void Player::transToPlanet()
{
    bool distDone = false;
    bool zoomDone = false;
    bool tiltDone = false;

    // counter-act planet rotation
    // TODO: stop and re correct? or not.... probably apply to final player trans
    m_distT->rotation.y = -m_world->getPosition()->rotation.y;

    // move out to planet
    // TODO: stop
    m_distT->translation.z +=
            TRANS_MOVE_SPEED * omi::fpsManager.getTimeScale();
    if ( m_distT->translation.z >= m_world->getDistance() )
    {
        m_distT->translation.z = m_world->getDistance();
        distDone = true;
    }

    // zoom in
    m_camPos->translation.z -=
        TRANS_ZOOM_SPEED * omi::fpsManager.getTimeScale();
    if ( m_camPos->translation.z <= ZOOM_DEFAULT_PO )
    {
        m_camPos->translation.z = ZOOM_DEFAULT_PO;
        zoomDone = true;
    }

    // tilt
    if ( m_camFocus->rotation.x <= 0.0f )
    {
        m_camFocus->rotation.x +=
            TRANS_TILT_SPEED * omi::fpsManager.getTimeScale();
        if ( m_camFocus->rotation.x >= 0.0f )
        {
            m_camFocus->rotation.x = 0.0f;
            tiltDone = true;
        }
    }
    else if ( m_camFocus->rotation.x > 0.0f )
    {
        m_camFocus->rotation.x -=
            TRANS_TILT_SPEED * omi::fpsManager.getTimeScale();
        if ( m_camFocus->rotation.x <= 0.0f )
        {
            m_camFocus->rotation.x = 0.0f;
            tiltDone = true;
        }
    }


    // check if the transition has eneded
    if ( distDone && zoomDone && tiltDone )
    {
        m_camFocus->parent = m_world->getPosition();
        m_state = gameplay::PLANET_ORBIT;
    }
}

void Player::planetOrbit()
{
    // regen time
    if ( m_generatingFuncs <= 1.0f )
    {
        m_generatingFuncs += REGEN_SPEED * omi::fpsManager.getTimeScale();
        m_gui->setReload( m_generatingFuncs );
    }

    attack();
}

void Player::attack()
{
    // calculate the focal point
    glm::mat4 rotMatrix( 1.0f );
    rotMatrix *= glm::rotate(
            m_camFocus->rotation.y * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 0.0f, 1.0f, 0.0f )
    );
    rotMatrix *= glm::rotate(
            m_camFocus->rotation.x * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 1.0f, 0.0f, 0.0f )
    );
    rotMatrix *= glm::translate( glm::vec3( 0.0f, 0.0f, 1.0f ) );
    glm::vec4 focalPoint4( 0.0f, 0.0f, 0.0f, 1.0f );

    focalPoint4 = rotMatrix * focalPoint4;
    glm::vec3 focalPoint = glm::normalize( focalPoint4.xyz() );

    // TODO: store
    float power = 0.1f;
    float distance = 0.75f;

    Function* func = NULL;
    // fire left function
    if ( omi::input::mousePressed( omi::input::mouse_button::LEFT ) &&
         m_generatingFuncs >= 1.0f )
    {
        func = new RaiseFunc( focalPoint, power, distance );
    }
    // fire right function
    else if ( omi::input::mousePressed( omi::input::mouse_button::RIGHT ) &&
         m_generatingFuncs >= 1.0f )
    {
        func = new LowerFunc( focalPoint, power, distance );
    }

    if ( func != NULL )
    {
        addEntity( new FunctionAttack(
                glm::vec3( 0.2, 0.6f, 1.0f ),
                m_world,
                focalPoint,
                m_camFocus->rotation,
                func
        ) );

        m_world->addFunction( func );
        m_generatingFuncs = 0.0f;
    }
}

void Player::initComponents()
{
    // transformations
    m_centrePos = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_centrePos );
    m_distT = new omi::Transform(
            "",
            m_centrePos,
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_distT );
    m_camFocus = new omi::Transform(
            "",
            m_distT,
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

    // music
    omi::Music* music = new omi::Music(
            "", "res/sound/music/to_the_void.ogg", 1.0f, true
    );
    m_components.add( music );
    music->play();
}
