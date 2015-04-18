#ifndef OMICRON_COMPONENT_PHYSICS_COLLISIONCHECKER_HPP_
#   define OMICRON_COMPONENT_PHYSICS_COLLISIONCHECKER_HPP_

#include <vector>

#include "src/omicron/component/physics/Physics.hpp"
#include "src/omicron/physics/bounding/BoundingShape.hpp"
#include "src/omicron/physics/collision_detect/CollisionDetect.hpp"
#include "src/omicron/utilities/VectorUtil.hpp"

namespace omi {

/**********************************************************\
| Component that is used to manually check for collisions. |
\**********************************************************/
class CollisionChecker : public Physics {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new collision checker with no initial bounding shapes
    @param id the identifier of the component */
    CollisionChecker( const std::string& id );

    /** Creates a new collision checker
    @param id the identifier of the component
    @param boundings a list of boundings to be used by this checker */
    CollisionChecker(
            const std::string& id,
            const std::vector<BoundingShape*>& boundings );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual component::Type getType() const
    {
        // a collision checker doesn't actually need any form of updating
        return component::SIMPLE;
    }

    /** @return the list of boundings in this checker */
    const std::vector<BoundingShape*> getBoundings() const;

    /** Adds a bounding shape to this
    @param bounding the new bounding shape to add */
    void addBounding( BoundingShape* bounding );

    // TODO: remove bounding

    /** Checks if the detector at the given position will collide with any
    boundings in the given group
    @param move the vector to move the boundings by
    @param group the group to check for collisions against
    @return whether this bounding is colliding at the position */
    bool forwardCheck( const glm::vec3& move, const std::string& group );

    /** Finds the best new position based on the given collision group
    @param move the vector to move the bounding by
    @param group the group to check collisions against
    @return the best position for the bounding */
    glm::vec3 forwardBestCheck(
            const glm::vec3& move,
            const std::string& group );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the list of boundings in this checker
    std::vector<BoundingShape*> m_boundings;
};

} // namespace omi

#endif
