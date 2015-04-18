#include "GlowBlurVertRenderTexture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GlowBlurVertRenderTexture::GlowBlurVertRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/glow_blur_vert_render_texture_fragment.glsl",
        0.5f
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GlowBlurVertRenderTexture::shaderParameters( GLuint program )
{
    // pass in resolution
    glUniform1f(
        glGetUniformLocation( program, "u_resolution" ),
        renderSettings.getResolution().y * m_resScale );
}

} // namespace omi
