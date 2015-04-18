#ifndef OMICRON_PHYSICS_COLLISION_DETECT_COLLISIONDETECT_H_
#   define OMICRON_PHYSICS_COLLISION_DETECT_COLLISIONDETECT_H_

#include <map>
#include <vector>

#include "lib/Utilitron/MacroUtil.hpp"

class CollisionDetector;
#include "src/omicron/component/physics/CollisionDetector.hpp"
#include "src/omicron/entity/Entity.hpp"
#include "src/omicron/physics/bounding/BoundingCircle.hpp"
#include "src/omicron/physics/bounding/BoundingRect.hpp"
#include "src/omicron/physics/bounding/BoundingSphere.hpp"

namespace omi {

struct CheckPair {
    std::string a;
    std::string b;
};

/**************************************************\
| Used for detecting collisions between boundings. |
\**************************************************/
class CollisionDetect {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_CONSTRUCTION(CollisionDetect);

public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Sets a collision group to be check against a second collision group
    @param a the first group to check
    @param b the second group to check against*/
    static void checkGroup(const std::string& a, const std::string& b);

    // TODO: remove groups check

    /** #Hidden
    Performs collision group detection for a frame */
    static void update();

    /** @param detector new collision detector to add */
    static void addDetector(CollisionDetector* detector);

    /** @param detector collision detector to remove */
    static void removeDetector(CollisionDetector* detector);

    /** Clears all bounding groups  */
    static void clear();

    /** Returns a list of bounding shapes the given bounding is colliding with
    in the given group
    @param bounding the bounding to check against the group
    @param group the group to check against
    @return the list of boundings from the group the first bounding is colliding
    with */
    static const std::vector<BoundingShape*> checkAgainstGroup(
            BoundingShape* bounding,
            const std::string& group );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the detectors
    static std::vector<CollisionDetector*> m_detectors;
    // groups to check
    static std::vector<CheckPair> m_check;

    // the collision detectors sorted by group, is updated once per cycle
    static std::map<std::string, std::vector<CollisionDetector*>> m_groups;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Process collision detection between two detectors */
    static void processDetectors(CollisionDetector* a, CollisionDetector* b);

    /** @return if the two bounding circles are colliding */
    static bool checkCollision(BoundingShape* a, BoundingShape* b);

    /** @return if the two bounding circles are colliding */
    static bool checkCircleCircle(BoundingCircle* a, BoundingCircle* b);

    /** @return if the two bounding rectangles are colliding */
    static bool checkRectRect( BoundingRect* a, BoundingRect* b );

    /** @return if the two bounding spheres are colliding */
    static bool checkSphereSphere( BoundingSphere* a, BoundingSphere* b );
};

} // namespace omi

#endif
