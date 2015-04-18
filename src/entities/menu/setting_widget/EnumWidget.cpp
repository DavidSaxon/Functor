#include "EnumWidget.hpp"

#include "src/data/Globals.hpp"
#include "src/omicron/Omicron.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

EnumWidget::EnumWidget(
        const glm::vec3& position,
        std::vector<std::string> values,
        unsigned defaultValue,
        unsigned currentValue )
    :
    SettingWidget ( position ),
    m_values      ( values ),
    m_defaultIndex( static_cast<int>( defaultValue ) ),
    m_currentIndex( static_cast<int>( currentValue ) ),
    m_revertIndex( 0 )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void EnumWidget::init()
{
    // create the text label
    omi::Transform* t = new omi::Transform(
            "",
            m_position,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( t );
    m_text = omi::ResourceManager::getText(
            "pause_secondary_item_text", "", t
    );
    m_text->gui = true;
    m_text->setString( m_values[ m_currentIndex ] );
    m_text->setHorCentred( true );
    m_text->setVertCentred( true );
    m_text->visible = false;
    m_components.add( m_text );

    // create the left arrow
    omi::Transform* t1 = new omi::Transform(
        "",
        m_position + glm::vec3( 0.3f, 0.0f, 0.0f ),
        glm::vec3( 0.0f, 0.0f, 180.0f ),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_leftArrow = omi::ResourceManager::getSprite(
            "enum_widget_arrow", "", t1 );
    m_leftArrow->gui = true;
    m_leftArrow->visible = false;
    m_components.add( m_leftArrow );

    // create the right arrow
    omi::Transform* t2 = new omi::Transform(
        "",
        m_position + glm::vec3( -0.3f, 0.0f, 0.0f ),
        glm::vec3(),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_rightArrow = omi::ResourceManager::getSprite(
            "enum_widget_arrow", "", t2 );
    m_rightArrow->gui = true;
    m_rightArrow->visible = false;
    m_components.add( m_rightArrow );
}

void EnumWidget::update()
{
    // do nothing if the widget is not active
    if ( !m_active )
    {
        m_arrowDown = false;
        return;
    }

    bool changed = false;
    if ( omi::input::isKeyPressed( omi::input::key::RIGHT ) &&
         !m_arrowDown                                          )
    {
        m_arrowDown = true;
        changed = true;
        ++m_currentIndex;
    }
    else if (
        omi::input::isKeyPressed( omi::input::key::LEFT ) &&
        !m_arrowDown                                         )
    {
        m_arrowDown = true;
        changed = true;
        --m_currentIndex;
    }
    else if ( !omi::input::isKeyPressed( omi::input::key::RIGHT ) &&
              !omi::input::isKeyPressed( omi::input::key::LEFT )  &&
               m_arrowDown                                           )
    {
        m_arrowDown = false;
    }

    // clamp the index
    if ( m_currentIndex < 0 )
    {
        m_currentIndex = m_values.size() - 1;
    }
    else if ( m_currentIndex >= static_cast<int>( m_values.size() ) )
    {
        m_currentIndex = 0;
    }

    // the value has changed
    if ( changed )
    {
        // update the text
        m_text->setString( m_values[ m_currentIndex ] );
    }
}

void EnumWidget::setActive( bool state )
{
    // super call
    SettingWidget::setActive( state );

    // colour the widget
    if ( state )
    {
        m_text->getMaterial().colour = global::MENU_ITEM_SELECTED_COLOUR;
        m_leftArrow->getMaterial().colour = global::MENU_ITEM_SELECTED_COLOUR;
        m_rightArrow->getMaterial().colour = global::MENU_ITEM_SELECTED_COLOUR;
    }
    else
    {
        m_text->getMaterial().colour = global::MENU_ITEM_NON_SELECTED_COLOUR;
        m_leftArrow->getMaterial().colour =
                global::MENU_ITEM_NON_SELECTED_COLOUR;
        m_rightArrow->getMaterial().colour =
                global::MENU_ITEM_NON_SELECTED_COLOUR;
    }
}

void EnumWidget::setVisible( bool state )
{
    m_text->visible = state;
    m_leftArrow->visible = state;
    m_rightArrow->visible = state;

    m_revertIndex = m_currentIndex;
}

void EnumWidget::resetDefault()
{
    m_currentIndex = m_defaultIndex;
    // update the text
    m_text->setString( m_values[ m_currentIndex ] );
}

void EnumWidget::revert()
{
    m_currentIndex = m_revertIndex;
    // update the text
    m_text->setString( m_values[ m_currentIndex ] );
}

const std::string& EnumWidget::getValue() const
{
    return m_values[ m_currentIndex ];
}
