#include "StartUp.hpp"

#include <iostream>

#include "src/functions/settings/Config.hpp"

namespace start_up {

omi::Scene* init()
{
    // TODO: should be true for final release
    // resources
    omi::ResourceServer::loadFromLibrary( false );

    // system settings
    omi::systemSettings.enableForcedLag( false );
    omi::systemSettings.setCursorHidden( true );

    // display settings
    omi::displaySettings.setPos( glm::vec2( -8.0, -29.0f ) );
    omi::displaySettings.setSize( omi::displaySettings.getScreenSize() );
    omi::displaySettings.setTitle( "Functor" );
    omi::displaySettings.setFrameRateCap( 60 );

    // render settings
    omi::renderSettings.setDepthTest( true );
    omi::renderSettings.setBackFaceCulling( true );
    omi::renderSettings.setClearColour( glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ) );
    omi::renderSettings.setColourPicking( true );
    omi::renderSettings.setVisibilityChecking( false );
    omi::renderSettings.setShadowFrustumSize( 20.0f );

    //audio settings
    omi::audioSettings.setSoundDisabled( false );
    omi::audioSettings.setMusicDisabled( false );

    // apply settings from disk
    settings::config::applySettingsFromConfig();

    return new StartUpScene();
}

} // namespace start_up
