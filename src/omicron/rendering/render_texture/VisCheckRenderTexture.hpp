#ifndef OMICRON_RENDERING_RENDER_TEXTURE_VISCHECKRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_VISCHECKRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

/***********************************************************\
| A render texture for checking if renderables are visible. |
\***********************************************************/
class VisCheckRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new visibility check render texture */
    VisCheckRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );
};

} // namespace omi

#endif
