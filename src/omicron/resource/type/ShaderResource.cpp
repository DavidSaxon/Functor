#include "ShaderResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

ShaderResource::ShaderResource(
          resource_group::ResourceGroup resourceGroup,
    const std::string&                  vertexPath,
    const std::string&                  fragmentPath)
    :
    Resource      (resourceGroup),
    m_vertexPath  (vertexPath),
    m_fragmentPath(fragmentPath) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

ShaderResource::~ShaderResource() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void ShaderResource::load() {

    if (!m_loaded) {

        m_shader = loader::loadShaderFromFiles(m_vertexPath, m_fragmentPath);
        m_loaded = true;
    }
}

void ShaderResource::release() {

    if (m_loaded) {

        glDeleteShader(m_shader.getVertexShader());
        glDeleteShader(m_shader.getFragmentShader());
        glDeleteProgram(m_shader.getProgram());
        m_shader = Shader();
        m_loaded = false;
    }
}

Shader ShaderResource::get() const {

    if (!m_loaded) {

        std::cout << "attempted to get unloaded shader" << std::endl;

        //TODO: throw an exception
    }

    return m_shader;
}

} // namespace omi