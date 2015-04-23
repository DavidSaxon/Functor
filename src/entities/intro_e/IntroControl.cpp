#include "IntroControl.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void IntroControl::init()
{
    m_state = intro::TITLE_FADE;
    m_fader = 0.0f;
    m_waiter = 0.0f;
    m_done = false;

    // camera
    omi::Transform* camPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 70.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( camPos );
    omi::Camera* camera =
            new omi::Camera( "", omi::cam::PERSPECTIVE, camPos, 50.0f );
    camera->setExposure( 1.2f );
    m_components.add( camera );

    // overlay
    omi::Sprite* overlay = omi::ResourceManager::getSprite(
            "pause_menu_overlay",
            "",
            NULL
    );
    overlay->gui = true;
    m_components.add( overlay );

    // suns
    m_sunRot = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    omi::Transform* sunPos1 = new omi::Transform(
            "",
            m_sunRot,
            glm::vec3( 12.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( sunPos1 );
    omi::Mesh* sunMesh1 =
            omi::ResourceManager::getMesh( "sun_std", "", sunPos1 );
    sunMesh1->getMaterial().glow =
                    new omi::Glow( glm::vec3( 1.0f, 0.2f, 0.2f ), 0.2f );
    m_components.add( sunMesh1 );
    omi::Transform* sunPos2 = new omi::Transform(
            "",
            m_sunRot,
            glm::vec3( -12.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( sunPos2 );
    omi::Mesh* sunMesh2 =
            omi::ResourceManager::getMesh( "sun_std", "", sunPos2 );
    sunMesh2->getMaterial().glow =
                    new omi::Glow( glm::vec3( 0.2f, 0.2f, 1.0f ), 0.2f );
    m_components.add( sunMesh2 );

    // planets
    omi::Transform* wPos1 = new omi::Transform(
            "",
            m_sunRot,
            glm::vec3( 0.0f, 0.0f, 57.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( wPos1 );
    omi::Mesh* wMesh1 =
            omi::ResourceManager::getMesh( "world_std", "", wPos1 );
    m_components.add( wMesh1 );

    omi::Transform* wPos2 = new omi::Transform(
            "",
            m_sunRot,
            glm::vec3( 67.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( wPos2 );
    omi::Mesh* wMesh2 =
            omi::ResourceManager::getMesh( "world_std", "", wPos2 );
    m_components.add( wMesh2 );

    omi::Transform* wPos3 = new omi::Transform(
            "",
            m_sunRot,
            glm::vec3( -63.0f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( wPos3 );
    omi::Mesh* wMesh3 =
            omi::ResourceManager::getMesh( "world_std", "", wPos3 );
    m_components.add( wMesh3 );

    omi::Transform* wPos4 = new omi::Transform(
            "",
            m_sunRot,
            glm::vec3( 0.0f, 0.0f, -68.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( wPos4 );
    omi::Mesh* wMesh4 =
            omi::ResourceManager::getMesh( "world_std", "", wPos4 );
    m_components.add( wMesh4 );


    omi::Transform* titlePos = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.1f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( titlePos );
    titleMainText =
            omi::ResourceManager::getText( "intro_title", "", titlePos );
    titleMainText->gui = true;
    titleMainText->setHorCentred( true );
    titleMainText->setVertCentred( true );
    m_components.add( titleMainText );

    omi::Transform* stPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, -0.1f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( stPos );
    titleUnderText =
            omi::ResourceManager::getText( "intro_sub_title", "", stPos );
    titleUnderText->gui = true;
    titleUnderText->setHorCentred( true );
    titleUnderText->setVertCentred( true );
    m_components.add( titleUnderText );

    m_storySprite =
            omi::ResourceManager::getSprite( "intro_info", "", NULL );
    m_storySprite->gui = true;
    m_storySprite->visible = false;
    m_components.add( m_storySprite );

    // music
    omi::Music* music = new omi::Music(
            "", "res/sound/music/former_of_worlds.ogg", 1.0f, true
    );
    m_components.add( music );
    music->play();
}

void IntroControl::update()
{
    // spin suns
    m_sunRot->rotation.y += 0.25f * omi::fpsManager.getTimeScale();

    switch ( m_state )
    {
        case intro::TITLE_FADE:
        {
            m_fader += 0.01f * omi::fpsManager.getTimeScale();
            if ( m_fader >= 1.0f )
            {
                m_fader = 1.0f;
                m_state = intro::TITLE_WAIT;
            }
            titleMainText->getMaterial().colour.a = m_fader;
            titleUnderText->getMaterial().colour.a = m_fader;
            break;
        }
        case intro::TITLE_WAIT:
        {
            m_waiter += 0.01f * omi::fpsManager.getTimeScale();
            if ( m_waiter >= 1.0f )
            {
                titleMainText->visible = false;
                titleUnderText->visible = false;
                m_storySprite->visible = true;
                m_state = intro::INFO;
            }
            break;
        }
        case intro::INFO:
        {
            if ( omi::input::isKeyPressed( omi::input::key::RETURN ) )
            {
                m_done = true;
            }
            break;
        }
    }
}

bool IntroControl::isDone()
{
    return m_done;
}
