#ifndef OMICRON_RENDERING_LIGHTING_SHADOWMAP_HPP_
#   define OMICRON_RENDERING_LIGHTING_SHADOWMAP_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <iostream>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtx/transform.hpp"

#include "src/omicron/Omicron.hpp"

namespace omi {

/******************************************************************************\
| A texture that can be rendered to and only contains depth for shadow mapping |
\******************************************************************************/
class ShadowMap {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new shadow map
    @param resScale the scale of the resolution the shadow map should be */
    ShadowMap( float resScale = 1.0f );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Binds the shadow map for rendering to */
    void bind();

    /** Reverts OpenGL to default to-screen rendering */
    void unbind();

    /** Reloads the shadow map */
    void reload();

    /** @return the texture the shadow map has been rendered to */
    GLuint getTexture() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the frame buffer
    GLuint m_frameBuffer;

    // the id of the texture to render to
    GLuint m_texture;

    // the scale of the resolution
    float m_resScale;
    // the current resolution of the texture
    glm::vec2 m_resolution;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Initialises the shadow map */
    void init();
};

}; // namespace omi

#endif
