#include "SettingWidget.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SettingWidget::SettingWidget( const glm::vec3& position )
    :
    m_active   ( false ),
    m_position ( position ),
    m_arrowDown( false )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void SettingWidget::init()
{
    // do nothing
}

void SettingWidget::update()
{
    // do nothing
}

void SettingWidget::setActive( bool state )
{
    m_active = state;
}
