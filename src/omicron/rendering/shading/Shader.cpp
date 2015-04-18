#include "Shader.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Shader::Shader() :
    m_vertex  (0),
    m_fragment(0),
    m_program (0) {
}

Shader::Shader(GLuint vertex, GLuint fragment, GLuint program) :
    m_vertex  (vertex),
    m_fragment(fragment),
    m_program (program) {
}

Shader::Shader(const Shader& other) :
    m_vertex  (other.m_vertex),
    m_fragment(other.m_fragment),
    m_program (other.m_program) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Shader::~Shader() {
}

//------------------------------------------------------------------------------
//                                   OPERATORS
//------------------------------------------------------------------------------

const Shader& Shader::operator=(const Shader& other) {

    m_vertex   = other.m_vertex;
    m_fragment = other.m_fragment;
    m_program  = other.m_program;

    return *this;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

GLuint Shader::getVertexShader() const {

    return m_vertex;
}

GLuint Shader::getFragmentShader() const {

    return m_fragment;
}

GLuint Shader::getProgram() const {

    return m_program;
}

} // namespace omi