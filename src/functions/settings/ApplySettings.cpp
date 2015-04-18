#include "ApplySettings.hpp"

#include <iostream>

#include "lib/Utilitron/StringUtil.hpp"

#include "src/data/Globals.hpp"
#include "src/omicron/Omicron.hpp"

namespace settings {

namespace apply {

void resolution( const std::string& value )
{
    // is true if the value cannot be read
    bool undefined = false;

    // find the divider
    unsigned p = value.find( 'x' );
    // check if the divider was found
    if ( p < value.length() )
    {
        // get the x and resolution values
        std::string xRes = value.substr( 0, p );
        std::string yRes = value.substr( p + 1, value.length() );

        // check that the values are integers
        if ( util::str::isInt( xRes ) && util::str::isInt( yRes ) )
        {
            // apply resolution
            omi::renderSettings.setResolution( glm::vec2(
                    atoi( xRes.c_str() ),
                    atoi( yRes.c_str() )
            ) );
        }
        else
        {
            undefined = true;
        }
    }
    else
    {
        undefined = true;
    }

    // the resolution could not be parsed, use the screen size
    if ( undefined )
    {
        // get the screen resolution
        omi::renderSettings.setResolution(
                omi::displaySettings.getScreenSize() );
    }
}

void fullscreen( const std::string& value )
{
    if ( value.compare( "off" ) == 0 )
    {
        omi::displaySettings.setFullscreen( false );
        // omi::displaySettings.setSize( omi::renderSettings.getResolution() );
    }
    else
    {
        omi::displaySettings.setFullscreen( true );
    }
}

void vsync( const std::string& value )
{
    if ( value.compare( "off" ) == 0 )
    {
        omi::displaySettings.setVsync( false );
    }
    else
    {
        omi::displaySettings.setVsync( true );
    }
}

void gamma( const std::string& value )
{
    float gamma = 0.6f;
    if ( util::str::isFloat( value )  )
    {
        float temp_val = static_cast<float>( atof( value.c_str() ) );
        if ( temp_val >= 0.0f && temp_val <= 1.0f )
        {
            gamma = temp_val;
        }
    }
    omi::renderSettings.setGammaCorrection( gamma );
}

void shadows( const std::string& value )
{
    if ( value.compare( "off" ) == 0 )
    {
        omi::renderSettings.setShadows( false );
    }
    else if ( value.compare( "low" ) == 0 )
    {
        omi::renderSettings.setShadows( true );
        omi::renderSettings.setShadowMapResolutionScale( 1.5f );
    }
    else if ( value.compare( "high" ) == 0 )
    {
        omi::renderSettings.setShadows( true );
        omi::renderSettings.setShadowMapResolutionScale( 4.0f );
    }
    else
    {
        omi::renderSettings.setShadows( true );
        omi::renderSettings.setShadowMapResolutionScale( 3.0f );
    }
}

void master( const std::string& value )
{
    float volume = 1.0f;
    if ( util::str::isFloat( value )  )
    {
        float temp_val = static_cast<float>( atof( value.c_str() ) );
        if ( temp_val >= 0.0f && temp_val <= 1.0f )
        {
            volume = temp_val;
        }
    }
    global::masterVolume = volume;
    omi::audioSettings.setSoundVolume(
        omi::audioSettings.getSoundVolume() *
        global::masterVolume
    );
    omi::audioSettings.setMusicVolume(
        omi::audioSettings.getMusicVolume() *
        global::masterVolume
    );
}

void sound( const std::string& value )
{
    float volume = 1.0f;
    if ( util::str::isFloat( value )  )
    {
        float temp_val = static_cast<float>( atof( value.c_str() ) );
        if ( temp_val >= 0.0f && temp_val <= 1.0f )
        {
            volume = temp_val;
        }
    }
    omi::audioSettings.setSoundVolume( volume * global::masterVolume );
}

void music( const std::string& value )
{
    float volume = 0.8f;
    if ( util::str::isFloat( value )  )
    {
        float temp_val = static_cast<float>( atof( value.c_str() ) );
        if ( temp_val >= 0.0f && temp_val <= 1.0f )
        {
            volume = temp_val;
        }
    }
    omi::audioSettings.setMusicVolume( volume * global::masterVolume );
}

void look( const std::string& value )
{
    float look = 1.0f;
    if ( util::str::isFloat( value )  )
    {
        float temp_val = static_cast<float>( atof( value.c_str() ) );
        if ( temp_val >= 0.0f && temp_val <= 2.0f )
        {
            look = temp_val;
        }
    }
    global::lookSensitivity = look;
}

void move( const std::string& value )
{
    if ( value.compare( "arrows" ) == 0 )
    {
        global::keyForwards  = omi::input::key::UP;
        global::keyBackwards = omi::input::key::DOWN;
        global::keyLeft      = omi::input::key::LEFT;
        global::keyRight     = omi::input::key::RIGHT;
    }
    else if ( value.compare( "esdf" ) == 0 )
    {
        global::keyForwards  = omi::input::key::E;
        global::keyBackwards = omi::input::key::D;
        global::keyLeft      = omi::input::key::S;
        global::keyRight     = omi::input::key::F;
    }
    else
    {
        global::keyForwards  = omi::input::key::W;
        global::keyBackwards = omi::input::key::S;
        global::keyLeft      = omi::input::key::A;
        global::keyRight     = omi::input::key::D;
    }
}

} // namespace apply

} // namespace settings
