#include "Help.hpp"

#include "src/data/Globals.hpp"

void Help::init()
{
    m_tutDone = false;
    m_timer = 0.0f;
    m_state = help::TO_START;

    omi::Transform* indexPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, -0.8f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( indexPos );
    m_indexText =
            omi::ResourceManager::getText( "level_select_help", "", indexPos );
    m_indexText->gui = true;
    m_indexText->setHorCentred( true );
    m_indexText->setVertCentred( true );
    m_indexText->setString( "Enter the index of the planet to attack..." );
    m_components.add( m_indexText );


    omi::Transform* rotPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.85f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( rotPos );
    m_rotateText =
            omi::ResourceManager::getText( "level_select_help", "", rotPos );
    m_rotateText->gui = true;
    m_rotateText->setHorCentred( true );
    m_rotateText->setVertCentred( true );
    m_rotateText->setString( "Move the mouse to rotate the camera." );
    m_components.add( m_rotateText );

    omi::Transform* scrollPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.75f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( scrollPos );
    m_zoomText =
            omi::ResourceManager::getText( "level_select_help", "", scrollPos );
    m_zoomText->gui = true;
    m_zoomText->setHorCentred( true );
    m_zoomText->setVertCentred( true );
    m_zoomText->setString( "Use the scroll wheel to zoom." );
    m_components.add( m_zoomText );

    m_tutPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, -0.2f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_tutPos2 = new omi::Transform(
            "",
            glm::vec3( 0.0f, -0.2f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );

    m_funcSprite =
            omi::ResourceManager::getSprite( "func_tut", "", m_tutPos );
    m_funcSprite->gui = true;
    m_funcSprite->visible = false;
    m_components.add( m_funcSprite );

    m_destroySprite =
            omi::ResourceManager::getSprite( "destroy_tut", "", m_tutPos2 );
    m_destroySprite->gui = true;
    m_destroySprite->visible = false;
    m_components.add( m_destroySprite );

    m_winSprite =
            omi::ResourceManager::getSprite( "win_tut", "", m_tutPos );
    m_winSprite->gui = true;
    m_winSprite->visible = false;
    m_components.add( m_winSprite );

    m_exitSprite =
            omi::ResourceManager::getSprite( "exit_tut", "", m_tutPos2 );
    m_exitSprite->gui = true;
    m_exitSprite->visible = false;
    m_components.add( m_exitSprite );


}

void Help::update()
{
    if ( global::m_inOrbit )
    {
        m_indexText->visible = false;
        m_rotateText->visible = false;
        m_zoomText->visible = false;

        if ( !m_tutDone )
        {
            m_state = help::FUNCTIONS;
            m_tutDone = true;
            m_timer = false;
        }
    }
    else
    {
        m_indexText->visible = true;
        m_rotateText->visible = true;
        m_zoomText->visible = true;
    }

    m_funcSprite->visible = false;
    m_destroySprite->visible = false;
    m_winSprite->visible = false;
    m_exitSprite->visible = false;

    float aspect = omi::renderSettings.getResolution().x /
                   omi::renderSettings.getResolution().y;

    m_tutPos->translation.x = -( aspect - 0.4f );
    m_tutPos2->translation.x = ( aspect - 0.4f );

    m_timer += 0.001f * omi::fpsManager.getTimeScale();

    switch ( m_state )
    {
        case help::FUNCTIONS:
        {
            m_funcSprite->visible = true;
            if ( m_timer >= 1.0f )
            {
                m_timer = 0.0f;
                m_state = help::DESTROY;
            }
            break;
        }
        case help::DESTROY:
        {
            m_destroySprite->visible = true;
            if ( m_timer >= 1.0f )
            {
                m_timer = 0.0f;
                m_state = help::WIN;
            }
            break;
        }
        case help::WIN:
        {
            m_winSprite->visible = true;
            if ( m_timer >= 1.0f )
            {
                m_timer = 0.0f;
                m_state = help::EXIT;
            }
            break;
        }
        case help::EXIT:
        {
            m_exitSprite->visible = true;
            if ( m_timer >= 1.0f )
            {
                m_timer = 0.0f;
                m_state = help::DONE;
            }
            break;
        }
        default:
        {
            // do nothing
            break;
        }
    }
}
