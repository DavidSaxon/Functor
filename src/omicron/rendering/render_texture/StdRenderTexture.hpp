#ifndef OMICRON_RENDERING_RENDER_TEXTURE_STDRENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_STDRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi {

class StdRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new standard render texture */
    StdRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );
};

} // namespace omi

#endif
