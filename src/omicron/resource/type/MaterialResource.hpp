#ifndef OMICRON_RESOURCE_TYPE_MATERIAL_RESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_MATERIAL_RESOURCE_H_

#include "src/omicron/resource/ResourceManager.hpp"

class ResourceManager;

#include "src/omicron/rendering/shading/Material.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/**********************************************\
| Contains the needed data to load a material. |
\**********************************************/
class MaterialResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new material resource
    @param resourceGroup the resource group of the material
    @param shader the resource id of the shader of the material
    @param colour the colour of the material
    @param texture the resource id of the texture of the material */
    MaterialResource(      resource_group::ResourceGroup resourceGroup,
                     const std::string&                  shader,
                     const glm::vec4&                    colour,
                     const std::string&                  texture,
                           unsigned                      flags );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded material */
    Material get() const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the resource id of the shader
    std::string m_shader;
    // the colour
    glm::vec4 m_colour;
    // the resource id of the texture
    std::string m_texture;
    // the flags of the material
    unsigned m_flags;

    // the omicron material
    Material m_material;
};

} // namespace omi

#endif
