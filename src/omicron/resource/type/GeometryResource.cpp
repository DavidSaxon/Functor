#include "GeometryResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

GeometryResource::GeometryResource(
              resource_group::ResourceGroup resourceGroup,
        const std::string&                  filePath)
    :
    Resource  ( resourceGroup ),
    m_filePath( filePath ) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

GeometryResource::~GeometryResource() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void GeometryResource::load() {

    if (!m_loaded) {

        m_geometry = t_GeometryPtr(loader::geoFromWavefront(m_filePath));
        m_loaded = true;
    }
}

void GeometryResource::release() {

    if (m_loaded) {

        m_geometry = t_GeometryPtr();
        m_loaded = false;
    }
}

Geometry* GeometryResource::get() {

    if (!m_loaded) {

        std::cout << "attempted to get unloaded geometry" << std::endl;

        //TODO: throw an exception
    }

    return m_geometry.get();
}

} // namepsace omi
