#include "LoadingSplash.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void LoadingSplash::init()
{
    // create the camera
    omi::Transform* camT = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.0f, 2.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( camT );
    omi::Camera* camera = new omi::Camera( "", omi::cam::PERSPECTIVE, camT );
    m_components.add( camera );

    // add point light to illuminate text
    omi::Transform* lightT = new omi::Transform(
            "",
            glm::vec3( 0.0f, 0.1f, 0.1f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( lightT );
    m_components.add( new omi::PointLight(
            "",
            lightT,
            0.6f,
            glm::vec3( 1.0f, 1.0f, 1.0f ),
            0.00f,
            2.0f,
            1.4f
    ) );

    // add the loading text
    omi::Text* loadingText =
            omi::ResourceManager::getText( "loading_text", "", NULL );
    // loadingText->gui = true; // TODO: maybe not?
    loadingText->setHorCentred( true );
    loadingText->setVertCentred( true );
    m_components.add( loadingText );
}

void LoadingSplash::update()
{
    // do nothing
}
