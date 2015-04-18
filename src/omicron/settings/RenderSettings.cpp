#include "RenderSettings.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

RenderSettings::RenderSettings() :
    m_change                  ( true ),
    m_depthTest               ( true ),
    m_backFaceCulling         ( true ),
    m_clearColour             ( 0.0f, 0.0f, 0.0f, 1.0f ),
    m_resolution              ( 1920, 1080 ),
    m_gammaCorrection         ( 1.0f ),
    m_ambientStrength         ( 0.5f ),
    m_ambientColour           ( 1.0f, 1.0f, 1.0f ),
    m_shadows                 ( false ),
    m_shadowFrustumSize       ( 20.0f ),
    m_shadowMapResolutionScale( 4.0f ),
    m_colourPicking           ( true ),
    m_visibiltyChecking       ( false ),
    m_blur                    ( false ),
    m_filmGrain               ( 0.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

//-----------------------------------GETTERS------------------------------------

bool RenderSettings::getDepthTest() const
{
    return m_depthTest;
}

bool RenderSettings::getBackFaceCulling() const
{
    return m_backFaceCulling;
}

const glm::vec4& RenderSettings::getClearColour() const
{
    return m_clearColour;
}

const glm::vec2& RenderSettings::getResolution() const
{
    return m_resolution;
}

float RenderSettings::getGammaCorrection() const
{
    return m_gammaCorrection;
}

float RenderSettings::getAmbientStrength() const
{
    return m_ambientStrength;
}

const glm::vec3& RenderSettings::getAmbientColour() const
{
    return m_ambientColour;
}

bool RenderSettings::getShadows() const
{
    return m_shadows;
}

float RenderSettings::getShadowFrustumSize() const
{
    return m_shadowFrustumSize;
}

float RenderSettings::getShadowMapResolutionScale() const
{
    return m_shadowMapResolutionScale;
}

bool RenderSettings::getColourPicking() const
{
    return m_colourPicking;
}

bool RenderSettings::getVisibilityChecking() const
{
    return m_visibiltyChecking;
}

bool RenderSettings::getBlur() const
{
    return m_blur;
}

float RenderSettings::getFilmGrain() const
{
    return m_filmGrain;
}

//-----------------------------------SETTERS------------------------------------

void RenderSettings::setDepthTest(bool depthTest)
{
    m_change = true;
    m_depthTest = depthTest;
}

void RenderSettings::setBackFaceCulling( bool backFaceCulling )
{
    m_change = true;
    m_backFaceCulling = backFaceCulling;
}

void RenderSettings::setClearColour( const glm::vec4& clearColour )
{
    m_change = true;
    m_clearColour = clearColour;
}

void RenderSettings::setResolution( const glm::vec2& resolution )
{
    m_change = true;
    m_resolution = resolution;
}

void RenderSettings::setGammaCorrection( float gamma )
{
    m_change = true;
    m_gammaCorrection = gamma;
}

void RenderSettings::setAmbientStrength( float strength )
{
    m_change = true;
    m_ambientStrength = strength;
}

void RenderSettings::setAmbientColour( const glm::vec3& colour )
{
    m_change = true;
    m_ambientColour = colour;
}

void RenderSettings::setShadows( bool shadows )
{
    m_change = true;
    m_shadows = shadows;
}

void RenderSettings::setShadowFrustumSize( float frustumSize )
{
    m_change = true;
    m_shadowFrustumSize = frustumSize;
}

void RenderSettings::setShadowMapResolutionScale( float scale )
{
    m_change = true;
    m_shadowMapResolutionScale = scale;
}

void RenderSettings::setColourPicking( bool state )
{
    m_change = true;
    m_colourPicking = state;
}

void RenderSettings::setVisibilityChecking( bool state )
{
    m_change = true;
    m_visibiltyChecking = state;
}

void RenderSettings::setBlur( bool state )
{
    m_change = true;
    m_blur = state;
}

void RenderSettings::setFilmGrain( float filmGrain )
{
    m_change = true;
    m_filmGrain = filmGrain;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool RenderSettings::check()
{
    bool temp = m_change;
    m_change = false;
    return temp;
}

} // namespace omi
