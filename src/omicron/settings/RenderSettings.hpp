#ifndef OMICRON_SETTINGS_RENDERSETTINGS_H_
#   define OMICRON_SETTINGS_RENDERSETTINGS_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "lib/glm/glm.hpp"
#include "lib/Utilitron/MacroUtil.hpp"

namespace omi {

/*************************************************************\
| An object that contains all settings relating to rendering. |
\*************************************************************/
class RenderSettings {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN( RenderSettings );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates new render settings initialised with default values */
    RenderSettings();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Hidden
    Checks if a change has been made to the settings */
    bool check();

    //---------------------------------GETTERS----------------------------------

    /** @return if depth testing is enabled */
    bool getDepthTest() const;

    /** @return if back face culling is enabled */
    bool getBackFaceCulling() const;

    /** @return the clear colour */
    const glm::vec4& getClearColour() const;

    /** @return the resolution being rendered to */
    const glm::vec2& getResolution() const;

    /** @return gamma correction value */
    float getGammaCorrection() const;

    /** @return the strength of the ambient light */
    float getAmbientStrength() const;

    /** @return the colour of the ambient light */
    const glm::vec3& getAmbientColour() const;

    /** @return whether shadows are enabled */
    bool getShadows() const;

    /** @return the shadow frustum size */
    float getShadowFrustumSize() const;

    /** @return the resolution scale of the shadow map */
    float getShadowMapResolutionScale() const;

    /** @return whether colour picking is used or not */
    bool getColourPicking() const;

    /** @return if render able visibility checking is on */
    bool getVisibilityChecking() const;

    /** @return if the rendered layers should be blurred */
    bool getBlur() const;

    /** @return the amount of film grain */
    float getFilmGrain() const;

    //---------------------------------SETTERS----------------------------------

    /** @param depthTest whether depth testing should be enabled */
    void setDepthTest(bool depthTest);

    /** @param backFaceCulling whether back face culling should be enabled */
    void setBackFaceCulling (bool backFaceCulling );

    /** @param clearColour the new clear colour */
    void setClearColour( const glm::vec4& clearColour );

    /** @param resolution the new resolution to be rendered to */
    void setResolution( const glm::vec2& resolution );

    /** @param gamma the new gamma correction value */
    void setGammaCorrection( float gamma );

    /** @param strength the new strength of ambient light */
    void setAmbientStrength( float strength );

    /** @param colour the new colour of ambient light */
    void setAmbientColour( const glm::vec3& colour );

    /** @param shadows sets whether shadows are on or not */
    void setShadows( bool shadows );

    /** @param frustumSize the size of the shadow frustum */
    void setShadowFrustumSize( float frustumSize );

    /** @param scale the scale of shadow map's resolution */
    void setShadowMapResolutionScale( float scale );

    /** @param state the state of colour picking */
    void setColourPicking( bool state );

    /** @param state the state of visibility checking */
    void setVisibilityChecking( bool state );

    /** @param state of blurring */
    void setBlur( bool state );

    /**@param filmGrain the amount of film grain to be applied to the final
              output */
    void setFilmGrain( float filmGrain );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // if a setting has changed
    bool m_change;

    // if depth testing is enabled
    bool m_depthTest;
    // if back face culling should be enabled
    bool m_backFaceCulling;
    // the clear colour
    glm::vec4 m_clearColour;

    // the resolution being rendered to
    glm::vec2 m_resolution;

    // the gamma correction value
    float m_gammaCorrection;

    // the strength of ambient light
    float m_ambientStrength;
    // the colour of ambient light
    glm::vec3 m_ambientColour;

    // whether shadows are enabled or not
    bool m_shadows;
    // the size of the shadow frustum
    float m_shadowFrustumSize;
    // the resolution of the shadow map
    float m_shadowMapResolutionScale;

    // whether Omicron will do colour picking for selection
    bool m_colourPicking;
    // whether Omicron should check if renderables are visible or not
    bool m_visibiltyChecking;

    // whether the rendered output should be blurred or not
    bool m_blur;

    // the amount of film grain to be applied to the final output
    float m_filmGrain;
};

} // namespace omi

#endif
