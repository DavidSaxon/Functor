#include "BlurVertRenderTexture.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

BlurVertRenderTexture::BlurVertRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/blur_vert_render_texture_fragment.glsl",
        1.0f
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void BlurVertRenderTexture::shaderParameters( GLuint program )
{
    // pass in resolution
    glUniform1f(
        glGetUniformLocation( program, "u_resolution" ),
        renderSettings.getResolution().y * m_resScale );
}

} // namespace omi
