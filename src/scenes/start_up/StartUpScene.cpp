#include "StartUpScene.hpp"

#include "src/functions/settings/Config.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void StartUpScene::init()
{
    // apply settings
    omi::renderSettings.setDepthTest( false );

    // load the needed resources
    omi::ResourceManager::load( resource_group::ALL );
    omi::ResourceManager::load( resource_group::DEBUG );
    omi::ResourceManager::load( resource_group::START_UP );

    // add entities
    m_omicronLogo = new OmicronLogo();
    addEntity( m_omicronLogo );
}

bool StartUpScene::update() {

    // wait until the omicron logo has performed its animation
    if ( m_omicronLogo->done() )
    {
        omi::ResourceManager::load( resource_group::LOADING );

        // start up finished
        return true;
    }

    return false;
}

omi::Scene* StartUpScene::nextScene()
{
    // release resources
    omi::ResourceManager::release( resource_group::START_UP );

    // revert settings
    omi::renderSettings.setDepthTest( true );

    // go to the loading scene
    return new LoadingScene();
}
