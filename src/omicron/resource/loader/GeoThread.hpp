#ifndef OMICRON_RESOURCE_LOADER_GEOTHREAD_HPP_
#   define OMICRON_RESOURCE_LOADER_GEOTHREAD_HPP_

#include "src/omicron/rendering/object_data/Geometry.hpp"

namespace omi {

namespace loader {

namespace geo_thread {

void concurrentLoadGeo( const std::string& path, Geometry* geo )
{
    // load the geometry
    Geometry* loadGeo = geoFromWavefront( path );

    // copy the geometry values over
    ( *geo ) = *loadGeo;
    delete loadGeo;
}

} // namespace geo_thread

} // namespace loader

} // namespace omi

#endif
