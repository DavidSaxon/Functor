#include "DisplaySettings.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

DisplaySettings::DisplaySettings() :
    m_change      ( true ),
    m_modeChange  ( false ),
    m_title       ( "Omicron" ),
    m_size        ( 640, 480 ),
    m_pos         ( 0, 0 ),
    m_centre      ( 320, 240 ),
    m_fullscreen  ( false ),
    m_frameRateCap( 60 ),
    m_vsync       ( false ),
    m_screenSize  ( 1920, 1080 )
{
}

//------------------------------------------------------------------------------
//                             PUBLIC MEMBER FUNCIONS
//------------------------------------------------------------------------------

bool DisplaySettings::check()
{
    bool temp = m_change;
    m_change = false;
    return temp;
}

bool DisplaySettings::checkMode()
{
    bool temp = m_modeChange;
    m_modeChange = false;
    return temp;
}

//-----------------------------------GETTERS------------------------------------

const std::string& DisplaySettings::getTitle() const
{
    return m_title;
}

const glm::vec2& DisplaySettings::getSize() const
{
    return m_size;
}

const glm::vec2 DisplaySettings::getPos() const
{
    return m_pos;
}

const glm::vec2& DisplaySettings::getCentre() const
{
    return m_centre;
}

bool DisplaySettings::getFullscreen() const
{
    return m_fullscreen;
}

unsigned DisplaySettings::getFrameRateCap() const
{
    return m_frameRateCap;
}

bool DisplaySettings::getVsync() const
{
    return m_vsync;
}

const glm::vec2& DisplaySettings::getScreenSize() const
{
    return m_screenSize;
}

//-----------------------------------SETTERS------------------------------------

void DisplaySettings::setTitle( const std::string& title )
{
    m_title = title;
    m_change = true;
}

void DisplaySettings::setSize( const glm::vec2& size )
{
    m_size = size;
    // update the centre pos
    m_centre.x = m_size.x / 2.0f;
    m_centre.y = m_size.y / 2.0f;
    m_change = true;
}

void DisplaySettings::setPos( const glm::vec2& pos )
{
    m_pos = pos;
    m_change = true;
}

void DisplaySettings::setFullscreen( bool fullscreen )
{
    if ( m_fullscreen != fullscreen )
    {
        m_modeChange = true;
    }
    m_fullscreen = fullscreen;
    m_change = true;
}

void DisplaySettings::setVsync( bool vsnyc )
{
    m_vsync = vsnyc;
    m_change = true;
}

void DisplaySettings::setFrameRateCap( unsigned cap )
{
    m_frameRateCap = cap;
    m_change = true;
}

void DisplaySettings::setScreenSize( const glm::vec2& screenSize )
{
    m_screenSize = screenSize;
}

} // namespace omi
