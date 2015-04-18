#include "MeshResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

MeshResource::MeshResource(
              resource_group::ResourceGroup resourceGroup,
              int                           layer,
        const std::string&                  geometry,
        const std::string&                  material)
    :
    Resource  (resourceGroup),
    m_layer   (layer),
    m_geometry(geometry),
    m_material(material) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

MeshResource::~MeshResource() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void MeshResource::load() {

    if (!m_loaded) {

        // meshes don't really need to load
        m_loaded = true;
    }
}

void MeshResource::release() {

    if (m_loaded) {

        // likewise they don't need to be delete
        m_loaded = false;
    }
}

Mesh* MeshResource::get(const std::string& id, Transform* transform) const {

    if (!m_loaded) {

        std::cout << "attempted to get unloaded mesh" << std::endl;
        //TODO: throw an exception
    }

    // create the mesh at the last minute
    return new Mesh(
        id, m_layer, transform,
        ResourceManager::getGeometry(m_geometry),
        ResourceManager::getMaterial(m_material)
    );
}

} // namespace omi
