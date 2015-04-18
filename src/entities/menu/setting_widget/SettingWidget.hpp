#ifndef REVERIE_ENTITIES_MENU_SETTING_WIDGET_SETTINGWIDGET_HPP_
#   define REVERIE_ENTITIES_MENU_SETTING_WIDGET_SETTINGWIDGET_HPP_

#include "src/omicron/entity/Entity.hpp"

/*****************************************************************************\
| Abstract base class for widgets that can be used to change a setting on the |
| menu. When widgets are active their values can be changed via the left and  |
| right arrow keys.                                                           |
\*****************************************************************************/
class SettingWidget : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new setting widget at the given position */
    SettingWidget( const glm::vec3& position );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual void init();

    /** Override */
    virtual void update();

    /** Sets the active state of the settings widget */
    virtual void setActive( bool state );

    /** Shows/hides the widget */
    virtual void setVisible( bool state ) = 0;

    /** Reset the widget to the default value */
    virtual void resetDefault() = 0;

    /** @return reverts the widget to the previously applied value */
    virtual void revert() = 0;

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // is true if the setting widget is active
    bool m_active;

    // the position of the widget
    glm::vec3 m_position;

    // is true if an arrow key is down
    bool m_arrowDown;
};

#endif
