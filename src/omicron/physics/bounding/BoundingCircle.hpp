#ifndef OMICRON_PHYSICS_BOUNDING_BOUNDINGCIRCLE_H_
#   define OMICRON_PHYSICS_BOUNDING_BOUNDINGCIRCLE_H_

#include "BoundingShape.hpp"

namespace omi {

/*******************************************\
| A two dimensional circle shaped bounding. |
\*******************************************/
class BoundingCircle : public BoundingShape {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new bounding circle with no offset
    @param radius the radius of the circle
    @param transform the transform to use for the circle'S location */
    BoundingCircle( float radius, Transform* transform ) :
        BoundingShape( bounding::CIRCLE, transform ),
        m_radius     ( radius )
    {
    }

    /** Creates a new bounding circle
    @param radius the radius of the circle
    @param transform the transform to use for the circle'S location
    @param offset the offset to use for the circles location*/
    BoundingCircle( float radius, Transform* transform,
            const glm::vec3& offset ) :
        BoundingShape(bounding::CIRCLE, transform, offset ),
        m_radius     ( radius )
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the radius of the circle */
    float getRadius() const
    {
        return m_radius;
    }

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the radius of the bounding circle
    float m_radius;
};

} // namespace omi

#endif
