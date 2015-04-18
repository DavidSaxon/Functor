#ifndef OMICRON_RENDERING_RENDER_TEXTURE_RENDERTEXTURE_HPP_
#   define OMICRON_RENDERING_RENDER_TEXTURE_RENDERTEXTURE_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <iostream>
#include <stdlib.h>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtx/transform.hpp"

#include "lib/Utilitron/MathUtil.hpp"

#include "src/omicron/Omicron.hpp"
#include "src/omicron/resource/loader/Loaders.hpp"

namespace omi {

/*******************************************************************\
| Abstract base class that all custom render textures inherit from. |
\*******************************************************************/
class RenderTexture {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor
    @param vertexShader the path to the vertex shader to use
    @param fragmentShader the path to the fragment shader to use
    @param resScale the scale of the resolution this texture should be
    @param filter the filter to use on the texture */
    RenderTexture(
            const std::string& vertexShader,
            const std::string& fragmentShader,
            float resScale = 1.0f,
            GLuint filter = GL_NEAREST );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Binds this as the texture to render to */
    void bind();

    /** Reverts OpenGL to default to-screen rendering */
    void unbind();

    /** Renders this texture to a quad in front of the screen */
    void render();

    /** Reloads the render texture */
    void reload();

    /** @return the OpenGL texture id */
    GLuint getTextureId() const;

    /** @return the resolution of the texture ( width and height ) */
    glm::vec2 getResolution() const;

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the id of the frame buffer being rendered to
    GLuint m_frameBuffer;
    // the depth buffer
    GLuint m_depthRenderBuffer;

    // the id of the texture to render to
    GLuint m_texture;

    // the path to the shaders
    std::string m_vertexShader;
    std::string m_fragmentShader;
    // the shader to render with
    Shader m_shader;
    // the scale of the resolution
    float m_resScale;
    // the current resolution of the texture
    glm::vec2 m_resolution;

    // the filter to use on the texture
    GLuint m_filter;

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Initialises this render texture */
    void init();

    /** Override to pass parameters in the shader */
    virtual void shaderParameters( GLuint program ) = 0;
};

} // namespace omi

#endif
