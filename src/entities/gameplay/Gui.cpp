#include "Gui.hpp"

#include <sstream>

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Gui::init()
{
    m_func1Boost = 0.0f;
    m_func2Boost = 0.0f;

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

    if ( global::pause )
    {
        return;
    }

    m_func1Boost -= 0.02f * omi::fpsManager.getTimeScale();
    m_func2Boost -= 0.02f * omi::fpsManager.getTimeScale();
    m_func1Boost = util::math::clamp<float>( m_func1Boost, 0.0f, 1.0f );
    m_func2Boost = util::math::clamp<float>( m_func2Boost, 0.0f, 1.0f );

    m_funcBoxSprite1->getMaterial().colour =
            glm::vec4( m_func1Boost, m_func1Boost, m_func1Boost, 0.5f );
    m_funcBoxSprite2->getMaterial().colour =
            glm::vec4( m_func2Boost, m_func2Boost, m_func2Boost, 0.5f );
}

void Gui::setVisible( bool state )
{
    m_targetSprite->visible = state;
    m_funcBoxSprite1->visible = state;
    m_funcBoxSprite2->visible = state;
    m_funcText1->visible = state;
    m_funcText2->visible = state;
    m_reloadBackSprite->visible = state;
    m_reloadFrontSprite->visible = state;
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
    ss << "power:    ";
    ss << std::setprecision( 3 ) << std::fixed;
    ss << power;
    m_powerText->setString( ss.str() );
}

void Gui::setDistance( float distance )
{
    std::stringstream ss;
    ss << "distance: ";
    ss << std::setprecision( 3 ) << std::fixed;
    ss << distance;
    m_distanceText->setString( ss.str() );
}

void Gui::setReload( float reload )
{
    m_targetSprite->visible = reload >= 1.0f ;

    reload = util::math::clamp( reload, 0.0f, 1.0f );
    m_reloadScale->scale.x = reload;
}

void Gui::boostFunc1()
{
    m_func1Boost = 1.0f;
}

void Gui::boostFunc2()
{
    m_func2Boost = 1.0f;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Gui::initComponents()
{
    //----------------------------------TARGET----------------------------------

    m_targetSprite = omi::ResourceManager::getSprite( "gui_target", "", NULL );
    m_targetSprite->gui = true;
    m_components.add( m_targetSprite );

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
    m_funcText1->setString( "" );
    m_funcText1->setHorCentred( true );
    // m_funcText1->setVertCentred( true );
    m_components.add( m_funcText1 );

    m_funcText2 = omi::ResourceManager::getText(
            "gui_function_text", "", func2Offset );
    m_funcText2->gui = true;
    m_funcText2->setString( "" );
    m_funcText2->setHorCentred( true );
    // m_funcText2->setVertCentred( true );
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
    m_powerText->setString( "   power: 0.0" );
    m_powerText->setHorCentred( true );
    m_powerText->setVertCentred( true );
    m_powerText->visible = false;
    // setDistance( 0.0f );
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
    m_distanceText->setString( "distance: 0.0" );
    m_distanceText->setHorCentred( true );
    m_distanceText->setVertCentred( true );
    m_distanceText->visible = false;
    // setPower( 0.0f );
    m_components.add( m_distanceText );


    //--------------------------------RELOAD BAR--------------------------------

    omi::Transform* reloadPos = new omi::Transform(
            "",
            m_funcPos,
            glm::vec3( global::FUNC_BOX_SIZE / 2.0f, 0.18f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    reloadPos->translation.x += 0.005f;
    m_components.add( reloadPos );
    m_reloadBackSprite = omi::ResourceManager::getSprite(
            "gui_reload_back", "", reloadPos );
    m_reloadBackSprite->gui = true;
    m_components.add( m_reloadBackSprite );


    m_reloadScale = new omi::Transform(
            "",
            reloadPos,
            glm::vec3(),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_reloadScale );
    m_reloadFrontSprite = omi::ResourceManager::getSprite(
            "gui_reload_front", "", m_reloadScale );
    m_reloadFrontSprite->gui = true;
    m_components.add( m_reloadFrontSprite );
}
