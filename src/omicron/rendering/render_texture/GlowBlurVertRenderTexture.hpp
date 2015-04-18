#ifndef OMICRON_RENDERING_RENDER_TEXTURE_GLOWBLURVERTRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_GLOWBLURVERTRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/***********************************************\
| Render texture the blurs vertically for glow. |
\***********************************************/
class GlowBlurVertRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new glow texture */
    GlowBlurVertRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );

};

} // namespace omi

#endif
