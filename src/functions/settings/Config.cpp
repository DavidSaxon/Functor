#include "Config.hpp"

#include <fstream>

#include "lib/Utilitron/StringUtil.hpp"

#include "src/data/Globals.hpp"
#include "src/functions/settings/ApplySettings.hpp"
#include "src/omicron/Omicron.hpp"

namespace settings {

namespace config {

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

// the path to the config file
static const std::string CONFIG_PATH = "config.omi_pref";

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

void applySettingsFromConfig()
{
    // open the file
    std::ifstream file( CONFIG_PATH.c_str() );

    // the settings values
    std::string resolution = "undefined";
    std::string fullscreen = "undefined";
    std::string vsync      = "undefined";
    std::string gamma      = "undefined";
    std::string shadows    = "undefined";
    std::string master     = "undefined";
    std::string sound      = "undefined";
    std::string music      = "undefined";
    std::string look       = "undefined";
    std::string move       = "undefined";

    // read what we can from the config file
    while ( file.good() )
    {
        // get the current line as a string
        char lineBuffer[ 2048 ];
        file.getline( lineBuffer, 2048 );
        std::string line( lineBuffer );

        // read resolution
        if ( util::str::beginsWith( line, "resolution:" ) )
        {
            parseConfigLine( line, resolution );
        }
        // read fullscreen
        else if ( util::str::beginsWith( line, "fullscreen:" ) )
        {
            parseConfigLine( line, fullscreen );
        }
        // read vsync
        else if ( util::str::beginsWith( line, "vsync:" ) )
        {
            parseConfigLine( line, vsync );
        }
        // read gamma
        else if ( util::str::beginsWith( line, "gamma:" ) )
        {
            parseConfigLine( line, gamma );
        }
        // read shadows
        else if ( util::str::beginsWith( line, "shadows:" ) )
        {
            parseConfigLine( line, shadows );
        }
        // read master volume
        else if ( util::str::beginsWith( line, "master:" ) )
        {
            parseConfigLine( line, master );
        }
        // read sound volume
        else if ( util::str::beginsWith( line, "sound:" ) )
        {
            parseConfigLine( line, sound );
        }
        // read music volume
        else if ( util::str::beginsWith( line, "music:" ) )
        {
            parseConfigLine( line, music );
        }
        // read look sensitivity
        else if ( util::str::beginsWith( line, "look:" ) )
        {
            parseConfigLine( line, look );
        }
        // read move keys
        else if ( util::str::beginsWith( line, "move:" ) )
        {
            parseConfigLine( line, move );
        }
    }

    // apply settings
    apply::resolution( resolution );
    apply::fullscreen( fullscreen );
    apply::vsync     ( fullscreen );
    apply::gamma     ( gamma );
    apply::shadows   ( shadows );
    apply::master    ( master );
    apply::sound     ( sound );
    apply::music     ( music );
    apply::look      ( look );
    apply::move      ( move );

    // write settings back to the config file
    writeConfig();
}

void parseConfigLine( const std::string& line, std::string& value )
{
    // split at the first space
    unsigned p = line.find( ' ' );
    if ( p < line.length() )
    {
        value = line.substr( p + 1, line.length() - p );
    }
}

void writeConfig()
{
    // open the config file
    std::ofstream file( CONFIG_PATH.c_str() );

    // write resolution
    file << "resolution: "
         << omi::renderSettings.getResolution().x << "x"
         << omi::renderSettings.getResolution().y << std::endl;
    // write fullscreen state
    file << "fullscreen: ";
    if ( omi::displaySettings.getFullscreen() )
    {
        file << "on" << std::endl;
    }
    else
    {
        file << "off" << std::endl;
    }
    // write vsync state
    file << "vsync: ";
    if ( omi::displaySettings.getVsync() )
    {
        file << "on" << std::endl;
    }
    else
    {
        file << "off" << std::endl;
    }
    // write gamma correction
    file << "gamma: " << omi::renderSettings.getGammaCorrection() << std::endl;
    // write shadows
    file << "shadows: ";
    if ( !omi::renderSettings.getShadows() )
    {
        file << "off" << std::endl;
    }
    else if ( omi::renderSettings.getShadowMapResolutionScale() < 2.0f )
    {
        file << "low" << std::endl;
    }
    else if ( omi::renderSettings.getShadowMapResolutionScale() < 3.5f )
    {
        file << "medium" << std::endl;
    }
    else
    {
        file << "high" << std::endl;
    }
    // write master volume
    file << "master: " << global::masterVolume << std::endl;
    // write sound volume
    file << "sound: " << omi::audioSettings.getSoundVolume() /
            global::masterVolume << std::endl;
    // write music volume
    file << "music: " << omi::audioSettings.getMusicVolume() /
            global::masterVolume << std::endl;
    // write look sensitivity
    file << "look: " << global::lookSensitivity << std::endl;
    // write move keys
    file << "move: ";
    if ( global::keyForwards == omi::input::key::W )
    {
        file << "wasd" << std::endl;
    }
    else if ( global::keyForwards == omi::input::key::E )
    {
        file << "esdf" << std::endl;
    }
    else
    {
        file << "arrows" << std::endl;
    }

    // clean up
    file.close();
}

} // namespace config

} // namespace settings
