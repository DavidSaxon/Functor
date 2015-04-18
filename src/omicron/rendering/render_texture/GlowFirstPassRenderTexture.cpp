#include "GlowFirstPassRenderTexture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GlowFirstPassRenderTexture::GlowFirstPassRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/glow_first_pass_render_texture_fragment.glsl",
        0.5f
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GlowFirstPassRenderTexture::shaderParameters( GLuint program )
{
    // do nothing
}

} // namespace omi
