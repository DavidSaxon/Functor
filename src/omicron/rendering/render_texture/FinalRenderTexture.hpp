#ifndef OMICRON_RENDERING_RENDER_TEXTURE_FINALRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_FINALRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/******************************************************************************\
| The final render texture is used to apply any signal-pass post processing to |
| the rendered image.                                                          |
\******************************************************************************/
class FinalRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new final render texture */
    FinalRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );
};

} // namespace omi

#endif
