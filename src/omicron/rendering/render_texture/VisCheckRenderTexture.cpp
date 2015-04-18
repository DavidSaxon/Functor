#include "VisCheckRenderTexture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

VisCheckRenderTexture::VisCheckRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/render_texture_fragment.glsl",
        0.1f
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void VisCheckRenderTexture::shaderParameters( GLuint program )
{
    // do nothing
}

} // namespace omi
