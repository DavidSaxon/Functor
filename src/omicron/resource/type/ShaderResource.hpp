#ifndef OMICRON_RESOURCE_TYPE_SHADER_RESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_SHADER_RESOURCE_H_

#include "src/omicron/rendering/shading/Shader.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/****************************************\
| contains needed data to load a shader. |
\****************************************/
class ShaderResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new shader resource
    @param resourceGroup the resource group of the shader
    @param vertexPath the path to the vertex shader
    @param fragmentPath the path to the fragment shader */
    ShaderResource(      resource_group::ResourceGroup resourceGroup,
                   const std::string&                  vertexPath,
                   const std::string&                  fragmentPath);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~ShaderResource();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded shader */
    Shader get() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the path to the vertex shader
    std::string m_vertexPath;
    // the path to the fragment shader
    std::string m_fragmentPath;

    // the omicron shader
    Shader m_shader;
};

} // namespace omi

#endif 