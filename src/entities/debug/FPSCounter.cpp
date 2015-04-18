#include "FPSCounter.hpp"

#include <sstream>

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

FPSCounter::FPSCounter()
    :
    m_timer( 1.1f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FPSCounter::init()
{
    // transform component to position the text
    omi::Transform* transform = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.85f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( transform );

    // create the text component
    m_text =
            omi::ResourceManager::getText( "fps_counter_text", "", transform );
    m_text->gui = true;
    m_text->setString( "0" );
    m_components.add( m_text );
}

void FPSCounter::update()
{
    // if the timer is up, update the text
    if ( m_timer > 1.0f )
    {
        // reset timer
        m_timer -= 1.0f;

        float fps = omi::fpsManager.getFPS();

        // colour text based on FPS
        // 60fps+ = green
        // 30fps+ = blue
        // 30fps- = red
        if ( fps > 60.0f )
        {
            m_text->getMaterial().colour = glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f );
        }
        else if ( fps > 30.0f )
        {
            m_text->getMaterial().colour = glm::vec4( 0.0f, 0.0f, 1.0f, 1.0f );
        }
        else
        {
            m_text->getMaterial().colour = glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f );
        }

        // set the text
        std::stringstream ss;
        ss << static_cast<int>( fps );
        m_text->setString( ss.str() );
    }

    // run the timer
    m_timer += 0.05f * omi::fpsManager.getTimeScale();
}
