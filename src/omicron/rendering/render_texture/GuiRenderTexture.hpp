#ifndef OMICRON_RENDERERING_RENDER_TEXTURE_GUIRENDERTEXTURE_HPP_
#   define OMICRON_RENDERERING_RENDER_TEXTURE_GUIRENDERTEXTURE_HPP_

#include "src/omicron/rendering/render_texture/RenderTexture.hpp"

namespace omi
{

class GuiRenderTexture : public RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new gui render texture */
    GuiRenderTexture();

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    virtual void shaderParameters( GLuint program );
};

} // namespace omi

#endif
