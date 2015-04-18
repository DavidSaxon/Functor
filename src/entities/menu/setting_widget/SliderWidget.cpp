#include "SliderWidget.hpp"

#include <iomanip>
#include <sstream>

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SliderWidget::SliderWidget(
        const glm::vec3& position,
        float low,
        float high,
        float defaultValue,
        float currentValue )
    :
    SettingWidget ( position ),
    m_low( low ),
    m_high( high ),
    m_default( defaultValue ),
    m_current( currentValue ),
    m_revert ( 0 )
{
    m_speed = ( m_high - m_low ) * 0.007f;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void SliderWidget::init()
{
    // create the bar
    omi::Transform* t = new omi::Transform(
        "",
        m_position,
        glm::vec3(),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( t );
    m_bar = omi::ResourceManager::getSprite(
            "slider_widget_bar", "", t );
    m_bar->gui = true;
    m_bar->visible = false;
    m_components.add( m_bar );

    // create the arrow
    m_arrowPos = new omi::Transform(
        "",
        m_position,
        glm::vec3(),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_arrowPos );
    m_arrow = omi::ResourceManager::getSprite(
            "slider_widget_arrow", "", m_arrowPos );
    m_arrow->gui = true;
    m_arrow->visible = false;
    m_components.add( m_arrow );

    // create the value text
    omi::Transform* t1 = new omi::Transform(
        "",
        m_position + glm::vec3( 0.35f, 0.0f, 0.0f ),
        glm::vec3(),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( t1 );
    m_text = omi::ResourceManager::getText(
            "pause_secondary_item_text", "", t1 );
    m_text->gui = true;
    std::stringstream ss;
    ss << std::fixed << std::setprecision( 2 ) << m_current;
    m_text->setString( ss.str() );
    m_text->setVertCentred( true );
    m_text->visible = false;
    m_components.add( m_text );

    updateUI();
}

void SliderWidget::update()
{
    // do nothing if the widget is not active
    if ( !m_active )
    {
        return;
    }

    // move the sliders values
    if ( omi::input::isKeyPressed( omi::input::key::RIGHT ) )
    {
        m_current += m_speed * omi::fpsManager.getTimeScale();
        if ( m_current >= m_high )
        {
            m_current = m_high;
        }
    }
    else if ( omi::input::isKeyPressed( omi::input::key::LEFT ) )
    {
        m_current -= m_speed * omi::fpsManager.getTimeScale();
        if ( m_current <= m_low )
        {
            m_current = m_low;
        }
    }

    updateUI();
}

void SliderWidget::setActive( bool state )
{
    // super call
    SettingWidget::setActive( state );

    // colour the widget
    if ( state )
    {
        m_bar->getMaterial().colour = global::MENU_ITEM_SELECTED_COLOUR;
        m_arrow->getMaterial().colour = global::MENU_ITEM_SELECTED_COLOUR;
        m_text->getMaterial().colour = global::MENU_ITEM_SELECTED_COLOUR;
    }
    else
    {
        m_bar->getMaterial().colour = global::MENU_ITEM_NON_SELECTED_COLOUR;
        m_arrow->getMaterial().colour = global::MENU_ITEM_NON_SELECTED_COLOUR;
        m_text->getMaterial().colour = global::MENU_ITEM_NON_SELECTED_COLOUR;
    }
}

void SliderWidget::setVisible( bool state )
{
    m_bar->visible = state;
    m_arrow->visible = state;
    m_text->visible = state;

    m_revert = m_current;
}

void SliderWidget::resetDefault()
{
    m_current = m_default;
    updateUI();
}

void SliderWidget::revert()
{
    m_current = m_revert;
    updateUI();
}

float SliderWidget::getValue() const
{
    return m_current;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void SliderWidget::updateUI()
{
    // position the arrow based on the value
    m_arrowPos->translation.x = m_position.x +
            ( ( ( m_current - ( ( m_high - m_low ) / 2.0f ) ) ) /
            ( m_high - m_low ) ) * 0.57f;

    // update text
    std::stringstream ss;
    ss << std::fixed << std::setprecision( 2 ) << m_current;
    m_text->setString( ss.str() );
}
