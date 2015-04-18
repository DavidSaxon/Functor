#include "BlurHorRenderTexture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

BlurHorRenderTexture::BlurHorRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/blur_hor_render_texture_fragment.glsl",
        1.0f
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void BlurHorRenderTexture::shaderParameters( GLuint program )
{
    // pass in resolution
    glUniform1f(
        glGetUniformLocation( program, "u_resolution" ),
        renderSettings.getResolution().x * m_resScale);
}

} // namespace omi
