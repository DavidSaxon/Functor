#include "Gui.hpp"

#include <sstream>

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Gui::init()
{
    initComponents();
    setVisible( false );
}

void Gui::update()
{
    // position based on aspect ratio
    float aspect = omi::renderSettings.getResolution().x /
                   omi::renderSettings.getResolution().y;

    m_funcPos->translation.x = -( aspect - ( global::FUNC_BOX_SIZE / 2.0f ) );
    m_funcPos->translation.x += 0.01f;

    m_mulPos->translation.x = aspect - 0.45f;
}

void Gui::setVisible( bool state )
{
    m_funcBoxSprite1->visible = state;
    m_funcBoxSprite2->visible = state;
    m_funcText1->visible = state;
    m_funcText2->visible = state;
    m_powerText->visible = state;
    m_distanceText->visible = state;
}

void Gui::setFunc1( const std::string& func1 )
{
    m_funcText1->setString( func1 );
}

void Gui::setFunc2( const std::string& func2 )
{
    m_funcText2->setString( func2 );
}

void Gui::setPower( float power )
{
    std::stringstream ss;
    ss << power;
    m_powerText->setString( ss.str() );
}

void Gui::setDistance( float distance )
{
    std::stringstream ss;
    ss << distance;
    m_distanceText->setString( ss.str() );
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Gui::initComponents()
{
    //--------------------------------FUNCTIONS---------------------------------

    // boxes
    m_funcPos = new omi::Transform(
            "",
            glm::vec3(),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_funcPos->translation.y =
            -1.0f + ( ( global::FUNC_BOX_SIZE / 2.0f ) + 0.01f );
    m_components.add( m_funcPos );
    m_funcBoxSprite1 = omi::ResourceManager::getSprite(
            "gui_function_box", "", m_funcPos );
    m_funcBoxSprite1->gui = true;
    m_components.add( m_funcBoxSprite1 );

    omi::Transform* func2Offset = new omi::Transform(
            "",
            m_funcPos,
            glm::vec3( global::FUNC_BOX_SIZE + 0.01f, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( func2Offset );
    m_funcBoxSprite2 = omi::ResourceManager::getSprite(
            "gui_function_box", "", func2Offset );
    m_funcBoxSprite2->gui = true;
    m_components.add( m_funcBoxSprite2 );

    m_funcText1 = omi::ResourceManager::getText(
            "gui_function_text", "", m_funcPos );
    m_funcText1->gui = true;
    m_funcText1->setString( "x*x" );
    m_funcText1->setHorCentred( true );
    m_funcText1->setVertCentred( true );
    m_components.add( m_funcText1 );

    m_funcText2 = omi::ResourceManager::getText(
            "gui_function_text", "", func2Offset );
    m_funcText2->gui = true;
    m_funcText2->setString( "sin(x)" );
    m_funcText2->setHorCentred( true );
    m_funcText2->setVertCentred( true );
    m_components.add( m_funcText2 );

    //-------------------------------MULTIPLIERS--------------------------------

    m_mulPos = new omi::Transform(
            "",
            glm::vec3( 0.0f, -0.73f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_mulPos );
    m_powerText = omi::ResourceManager::getText(
            "gui_mul_text", "", m_mulPos );
    m_powerText->gui = true;
    m_powerText->setString( "   power: 0.25" );
    m_powerText->setHorCentred( true );
    m_powerText->setVertCentred( true );
    m_components.add( m_powerText );

    omi::Transform* m_mulOffset = new omi::Transform(
            "",
            m_mulPos,
            glm::vec3( 0.0f, -0.12f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_mulOffset );
    m_distanceText = omi::ResourceManager::getText(
            "gui_mul_text", "", m_mulOffset );
    m_distanceText->gui = true;
    m_distanceText->setString( "distance: 0.67" );
    m_distanceText->setHorCentred( true );
    m_distanceText->setVertCentred( true );
    m_components.add( m_distanceText );

}
