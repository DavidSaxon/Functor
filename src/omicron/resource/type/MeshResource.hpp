#ifndef OMICRON_RESOURCE_TYPE_MESHRESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_MESHRESOURCE_H_

#include "src/omicron/resource/ResourceManager.hpp"

class ResourceManager;

#include "src/omicron/component/renderable/Mesh.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/******************************************\
| Contains the needed data to load a mesh. |
\******************************************/
class MeshResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new mesh resource
    @param resourceGroup the resource group of the mesh
    @param layer the layer of the mesh
    @param geometry the resource id of the meshes' geometry
    @param material the resource id of the meshes' material */
    MeshResource(      resource_group::ResourceGroup resourceGroup,
                       int                           layer,
                 const std::string&                  geometry,
                 const std::string&                  material);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~MeshResource();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded mesh
    @param id the component identifier of the mesh
    @param transform the transform to use for the mesh*/
    Mesh* get(const std::string& id, Transform* transform) const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the layer of the mesh
    int m_layer;
    // the resource id of the meshes' geometry
    std::string m_geometry;
    // the resource id of the meshes' material
    std::string m_material;
};

} // namespace omi

#endif
