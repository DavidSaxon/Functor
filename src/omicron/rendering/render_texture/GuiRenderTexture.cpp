#include "GuiRenderTexture.hpp"

namespace omi
{

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GuiRenderTexture::GuiRenderTexture() :
    RenderTexture(
        "res/gfx/shader/omicron/render_texture_vertex.glsl",
        "res/gfx/shader/omicron/gui_render_texture_fragment.glsl"
    )
{
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GuiRenderTexture::shaderParameters( GLuint program )
{
    // pass in gamma
    glUniform1f(
        glGetUniformLocation( program, "u_gamma" ),
        renderSettings.getGammaCorrection() );
}

} // namespace omi
