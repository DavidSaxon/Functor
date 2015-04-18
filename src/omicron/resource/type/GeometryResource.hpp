#ifndef OMICRON_RESOURCE_TYPE_GEOMETRYRESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_GEOMETRYRESOURCE_H_

#include <memory>

#include "src/omicron/rendering/object_data/Geometry.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

//-------------------------------TYPE DEFINITIONS-------------------------------

typedef std::unique_ptr<Geometry> t_GeometryPtr;

/********************************************\
| Contains the needed data to load geometry. |
\********************************************/
class GeometryResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new geometry resource
    @param resourceGroup the resource group of the geometry
    @param filePath the path to the geometry file */
    GeometryResource(      resource_group::ResourceGroup resourceGroup,
                     const std::string&                  filePath);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~GeometryResource();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded geometry */
    Geometry* get();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the file path to load the geometry from
    std::string m_filePath;

    // the geometry
    t_GeometryPtr m_geometry;

};

} // namespace omi

#endif
