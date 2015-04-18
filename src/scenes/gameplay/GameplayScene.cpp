#include "GameplayScene.hpp"

#include "src/omicron/input/Input.hpp"

#include "src/entities/debug/FPSCounter.hpp"

#include "src/entities/gameplay/Player.hpp"
#include "src/entities/gameplay/environment/Sun.hpp"
#include "src/entities/gameplay/environment/World.hpp"
#include "src/entities/menu/PauseMenu.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GameplayScene::init()
{
    // apply lock the mouse to the centre of the screen
    omi::systemSettings.setCursorLocked( true );
    omi::systemSettings.setCursorLockPosition(
            omi::displaySettings.getCentre() );


    omi::renderSettings.setClearColour( glm::vec4( 0.9f, 0.9f, 0.9f, 1.0f ) );

    // ambient lighting
    omi::renderSettings.setAmbientStrength( 0.5f );
    omi::renderSettings.setAmbientColour( glm::vec3( 1.0f, 1.0f, 1.0f ) );
    omi::renderSettings.setFilmGrain( 0.04f );

    // TODO: REMOVE ME
    // addEntity( new FPSCounter() );

    // add the initial entities
    addEntity( new PauseMenu() );

    addEntity( new Sun() );

    std::vector<World*> worlds;
    worlds.push_back( new World( 0.25f,  20.0f, 0.02f, "orbit_20" ) );
    worlds.push_back( new World( 0.4f,  30.0f, -0.02f, "orbit_30" ) );
    worlds.push_back( new World( -0.3f, 40.0f, 0.01f, "orbit_40" ) );

    addEntity( worlds[ 0 ] );
    addEntity( worlds[ 1 ] );
    addEntity( worlds[ 2 ] );

    addEntity( new Player( worlds ) );
}

bool GameplayScene::update()
{
    // TODO: REMOVE ME
    if ( omi::input::isKeyPressed( omi::input::key::F7 ) )
    {
        // TODO: go to menu
        return true;
    }

    return false;
}

omi::Scene* GameplayScene::nextScene()
{
    // revert settings
    omi::systemSettings.setCursorLocked( false );

    return NULL;

}
