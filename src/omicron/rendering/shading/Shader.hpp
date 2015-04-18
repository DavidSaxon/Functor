#ifndef OMICRON_RENDERING_SHADING_SHADER_H_
#   define OMICRON_RENDERING_SHADING_SHADER_H_

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

namespace omi {

/*******************************\
| Wrapper for an OpenGL shader. |
\*******************************/
class Shader {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a null shader */
    Shader();

    /** Creates a shader with the given OpenGL pointers
    @param vertex the OpenGL pointer to the vertex shader
    @param fragment the OpenGL pointer to the fragment shader
    @param program the OpenGL to the program */
    Shader(GLuint vertex, GLuint fragment, GLuint program);

    /** Creates a copy of the given shader
    @param other the shader to copy from */
    Shader(const Shader& other);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~Shader();

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /** Assigns the values of the given shader to this shader
    @param other the shader to copy from */
    const Shader& operator=(const Shader& other);

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the OpenGL pointer to the vertex shader */
    GLuint getVertexShader() const;

    /** @return the OpenGL pointer to the fragment shader */
    GLuint getFragmentShader() const;

    /** @return the OpenGL pointer to the program */
    GLuint getProgram() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the vertex shader
    GLuint m_vertex;
    // the fragment shader
    GLuint m_fragment;
    // the OpenGL program
    GLuint m_program;
};

} // namespace omi

#endif