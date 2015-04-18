#ifndef OMICRON_RESOURCE_TYPE_KEYMESHRESOURCE_HPP_
#   define OMICRON_RESOURCE_TYPE_KEYMESHRESOURCE_HPP_

#include <map>
#include <vector>

#include "src/omicron/resource/ResourceManager.hpp"

class ResourceManager;

#include "src/omicron/component/renderable/KeyFrameMesh.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/*****************************************************\
| Contains the needed data to load a key framed mesh. |
\*****************************************************/
class KeyFrameMeshResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new key frame mesh resource
    @param resourceGroup the resource group of the key frame mesh
    @param layer the layer of the mesh
    @param material the resource id of the meshes' material
    @param filePath the file path for the meshes */
    KeyFrameMeshResource(
            resource_group::ResourceGroup resourceGroup,
            int                           layer,
            const std::string&            material,
            const std::string&            filePath );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded key frame mesh with geometry
    @param id the component identifier of the key frame mesh
    @param transform the transform to use with the key frame mesh */
    KeyFrameMesh* get( const std::string& id, Transform* transform ) const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the layer of the mesh
    int m_layer;
    // the id of the material to use
    std::string m_material;
    // the file path to load the key frame mesh from
    std::string m_filePath;

    // map from animation names to the respective geometry keys
    std::map<std::string, std::vector<Geometry*>> m_geoMap;
    // a map from animation names to the frames between each key
    std::map<std::string, std::vector<unsigned>> m_frameMap;
    // the name of the default animation
    std::string m_defaultAni;
};

} // namespace omi

#endif
