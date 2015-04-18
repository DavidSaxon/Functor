#ifndef OMICRON_RENDERING_OBJECT_DATA_GEOMETRY_H_
#   define OMICRON_RENDERING_OBJECT_DATA_GEOMETRY_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <vector>

#include "lib/glm/glm.hpp"

namespace omi {

//-----------------------------------TYPEDEF------------------------------------

typedef std::vector<glm::vec3> t_VertexArray;
typedef std::vector<glm::vec2> t_UVArray;
typedef std::vector<glm::vec3> t_NormalArray;

/****************************************************************************\
| A collection of data that describes vertices, UV coordinates, and normals. |
\****************************************************************************/
class Geometry {
public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    //! the vertices of the geometry
    t_VertexArray vertices;
    //! the UV coordinates of the geometry
    t_UVArray     uv;
    //! the normals of the geometry
    t_NormalArray normals;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates new empty geometry */
    Geometry()
    {
    }

    /** Creates a new collection of geometry data using the given data
    @param a_vertices the vertices of the geometry
    @param a_uv the UV coordinates of the geometry
    @param a_normals the normals of the geometry */
    Geometry(const t_VertexArray& a_vertices,
             const t_UVArray&     a_uv,
             const t_NormalArray& a_normals) :
        vertices(a_vertices),
        uv      (a_uv),
        normals (a_normals) {
    }

    /** Creates a copy of the given geometry data
    @param other the geometry to copy from */
    Geometry(const Geometry& other) :
        vertices(other.vertices),
        uv      (other.uv),
        normals (other.normals) {
    }

    //--------------------------------------------------------------------------
    //                                 OPERATORS
    //--------------------------------------------------------------------------

    /** Assigns the data of this geometry to a copy of the data from the other
    given geometry
    @param other the geometry to copy from */
    const Geometry& operator=(const Geometry& other) {

        vertices = other.vertices;
        uv       = other.uv;
        normals  = other.normals;

        return *this;
    }
};

} // namespace omi

#endif
