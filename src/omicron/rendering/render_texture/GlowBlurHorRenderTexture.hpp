#ifndef OMICRON_RENDERING_RENDER_TEXTURE_GLOWBLURHORRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_GLOWBLURHORRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/*********************************************************\
| Render texture that blurs horizontally to perform glow. |
\*********************************************************/
class GlowBlurHorRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new glow texture */
    GlowBlurHorRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );

};

} // namespace omi

#endif
