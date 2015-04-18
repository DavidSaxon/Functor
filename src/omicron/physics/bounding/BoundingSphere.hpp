#ifndef OMICRON_PHYSICS_BOUNDING_BOUNDINGSPHERE_HPP_
#   define OMICRON_PHYSICS_BOUNDING_BOUNDINGSPHERE_HPP_

#include "BoundingShape.hpp"

namespace omi {

/*********************************************\
| A three dimensional sphere shaped bounding. |
\*********************************************/
class BoundingSphere : public BoundingShape {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new bounding sphere with no offset
    @param radius the radius of the sphere
    @param transform the transform to use for the sphere's location */
    BoundingSphere( float radius, Transform* transform ) :
        BoundingShape( bounding::SPHERE, transform ),
        m_radius     ( radius )
    {
    }

    /** Creates a new bounding sphere
    @param radius the radius of the sphere
    @param transform the transform to use for the sphere's location
    @param offset the offset to use for the sphere's location */
    BoundingSphere(
            float radius,
            Transform* transform,
            const glm::vec3& offset ) :
        BoundingShape( bounding::SPHERE, transform, offset ),
        m_radius( radius )
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the radius of the sphere */
    float getRadius() const
    {
        return m_radius;
    }

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the radius of the bounding sphere
    float m_radius;
};

} // namespace omi

#endif
