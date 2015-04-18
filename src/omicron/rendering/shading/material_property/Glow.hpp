#ifndef OMICRON_RENDERING_SHADING_MATERIAL_PROPERTY_GLOW_HPP_
#   define OMICRON_RENDERING_SHADING_MATERIAL_PROPERTY_GLOW_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include "lib/glm/glm.hpp"

#include "src/omicron/rendering/shading/Texture.hpp"

namespace omi {

/******************************************************************************\
| The glow property defines the existence and behavior of a material's glowing |
| radius.                                                                      |
\******************************************************************************/
class Glow {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new glow property
    @param colour the colour of the glow halo which must have a combined rgb
                  value of 0.05
    @param brightness the brightness of the glow
    @param texture the texture of the glow */
    Glow( const glm::vec3& colour, float brightness, Texture* texture = NULL );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    //---------------------------------GETTERS----------------------------------

    /** @return the colour of the glow halo */
    const glm::vec3& getColour() const;

    /** @return the brightness of the glow */
    float getBrightness() const;

    /** @return the texture of the colour */
    Texture* getTexture();

    //---------------------------------SETTERS----------------------------------

    /** @param colour the colour of the glow halo */
    void setColour( const glm::vec3& colour );

    /** @param brightness the brightness of the glow */
    void setBrightness( float brightness );

    void setTexture( Texture* texture );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the colour of the glow
    glm::vec3 m_colour;
    // the brightness of the glow
    float m_brightness;
    // the texture of the glow
    Texture* m_texture;
};

} // namespace omi

#endif

