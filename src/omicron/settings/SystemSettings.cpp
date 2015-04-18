#include "SystemSettings.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SystemSettings::SystemSettings() :
    m_change           ( true ),
    m_cursorHidden     ( false ),
    m_cursorLocked     ( false ),
    m_enableEnforcedLag( false ),
    m_enforcedLag1     ( 100 ),
    m_enforcedLag2     ( 250 ),
    m_enforcedLag3     ( 500 )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool SystemSettings::check()
{
    bool temp = m_change;
    m_change = false;
    return temp;
}

//-----------------------------------GETTERS------------------------------------

bool SystemSettings::isCursorHidden() const
{
    return m_cursorHidden;
}

bool SystemSettings::isCursorLocked() const
{
    return m_cursorLocked;
}

const glm::vec2& SystemSettings::getCursorLockedPos() const
{
    return m_cursorLockPos;
}

bool SystemSettings::isEnforcedLagEnabled() const
{
    return m_enableEnforcedLag;
}

unsigned SystemSettings::getEnforcedLag1() const
{
    return m_enforcedLag1;
}

unsigned SystemSettings::getEnforcedLag2() const
{
    return m_enforcedLag2;
}

unsigned SystemSettings::getEnforcedLag3() const
{
    return m_enforcedLag3;
}

//-----------------------------------SETTERS------------------------------------

void SystemSettings::setCursorHidden(bool hidden)
{
    m_cursorHidden = hidden;
    m_change = true;
}

void SystemSettings::setCursorLocked(bool locked)
{
    m_cursorLocked = locked;
    m_change = true;
}

void SystemSettings::setCursorLockPosition(const glm::vec2& pos)
{
    m_cursorLockPos = pos;
    m_change = true;
}

void SystemSettings::enableForcedLag( bool state )
{
    m_enableEnforcedLag = true;
    m_change = true;
}

void SystemSettings::setEnforcedLag1( unsigned interval )
{
    m_enforcedLag1 = interval;
    m_change = true;
}

void SystemSettings::setEnforcedLag2( unsigned interval )
{
    m_enforcedLag2 = interval;
    m_change = true;
}

void SystemSettings::setEnforcedLag3( unsigned interval )
{
    m_enforcedLag3 = interval;
    m_change = true;
}

} // namespace omi
