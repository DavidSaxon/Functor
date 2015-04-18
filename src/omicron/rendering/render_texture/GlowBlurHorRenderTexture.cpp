#include "GlowBlurHorRenderTexture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GlowBlurHorRenderTexture::GlowBlurHorRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/glow_blur_hor_render_texture_fragment.glsl",
        0.5f
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GlowBlurHorRenderTexture::shaderParameters( GLuint program )
{
    // pass in resolution
    glUniform1f(
        glGetUniformLocation( program, "u_resolution" ),
        renderSettings.getResolution().x * m_resScale);
}

} // namespace omi
