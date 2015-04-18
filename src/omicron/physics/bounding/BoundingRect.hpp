#ifndef OMICRON_PHYSICS_BOUNDING_BOUNDINGRECT_HPP_
#   define OMICRON_PHYSICS_BOUNDING_BOUNDINGRECT_HPP_

#include "BoundingShape.hpp"

namespace omi {

/*********************************************\
| A two dimensional rectangle shaped bounding |
\*********************************************/
class BoundingRect : public BoundingShape {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new bounding rectangle with no offset
    @param size the width and height of the rectangle
    @param transform the transform to use for the rectangle's location */
    BoundingRect(
            const glm::vec2& size,
            Transform* transform,
            bounding::Direction direction = bounding::ALL )
        :
        BoundingShape( bounding::RECTANGLE, transform, direction ),
        m_size( size )
    {
    }

    /** Creates a new bounding rectangle
    @param size the width and height of the rectangle
    @param transform the transform to use for the rectangle's location
    @param offset the offset to use for the rectangle's location */
    BoundingRect(
            const glm::vec2& size,
            Transform* transform,
            const glm::vec3& offset,
            bounding::Direction direction = bounding::ALL )
        :
        BoundingShape( bounding::RECTANGLE, transform, offset, direction ),
        m_size( size )
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the size of the rectangle */
    const glm::vec2& getSize() const
    {
        return m_size;
    }

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the size of the rectangle
    glm::vec2 m_size;

};

} // namespace omi

#endif
