#ifndef OMICRON_RENDERING_RENDER_TEXTURE_BLURVERTRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_BLURVERTRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/***************************\
| Render texture that blurs |
\***************************/
class BlurVertRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new blur texture */
    BlurVertRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );

};

} // namespace omi

#endif
