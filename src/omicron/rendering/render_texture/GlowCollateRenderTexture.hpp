#ifndef OMICRON_RENDERING_RENDER_TEXTURE_GLOWCOLLATERENDERTEXTIRE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_GLOWCOLLATERENDERTEXTIRE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/******************************************************************************\
| Render texture that makes any render data that has a combined rgb value less |
| than 0.05 transparent.                                                       |
\******************************************************************************/
class GlowCollateRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new glow first pass texture */
    GlowCollateRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );

};

} // namespace omi

#endif
