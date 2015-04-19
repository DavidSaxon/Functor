#include "LoadingScene.hpp"


#include "src/entities/loading/LoadingSplash.hpp"
#include "src/scenes/gameplay/GameplayScene.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void LoadingScene::init()
{
    // ambient lighting
    omi::renderSettings.setAmbientStrength( 0.0f );

    m_firstUpdate = true;
    m_loadingDone = false;

    // addEntity( new LoadingSplash() );
}

bool LoadingScene::update()
{
    // start loading on the second update
    if ( !m_firstUpdate && !m_loadingDone )
    {
        omi::ResourceManager::load( resource_group::MENU );
        omi::ResourceManager::load( resource_group::GUI );
        omi::ResourceManager::load( resource_group::PLAYER );
        omi::ResourceManager::load( resource_group::ENVIRONMENT );
        omi::ResourceManager::load( resource_group::EFFECTS );

        m_loadingDone = true;

        // loading is finished go to the next scene
        return true;
    }
    else if ( m_firstUpdate )
    {
        m_firstUpdate = false;
    }

    return false;
}

omi::Scene* LoadingScene::nextScene()
{
    // TODO: release resources
    omi::ResourceManager::release( resource_group::LOADING );

    return new GameplayScene();
}
