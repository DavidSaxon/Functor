#include "IntroScene.hpp"

#include "src/scenes/gameplay/GameplayScene.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void IntroScene::init()
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

    omi::renderSettings.setBlur( true );

    introC = new IntroControl();
    addEntity( introC );
}

bool IntroScene::update()
{
    return introC->isDone();
}

omi::Scene* IntroScene::nextScene()
{
    omi::renderSettings.setBlur( false );

    return new GameplayScene();
}
