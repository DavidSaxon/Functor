#ifndef OMICRON_RENDERING_RENDER_TEXTURE_BLURHORRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_BLURHORRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/*****************************************\
| Render texture that blurs horizontally. |
\*****************************************/
class BlurHorRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a blur texture */
    BlurHorRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );

};

} // namespace omi

#endif
