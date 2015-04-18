#ifndef OMICRON_COMPONENT_PHYSICS_COLLISIONDETECTOR_H_
#   define OMICRON_COMPONENT_PHYSICS_COLLISIONDETECTOR_H_

#include <algorithm>
#include <memory>
#include <vector>

#include "src/omicron/component/physics/Physics.hpp"
#include "src/omicron/physics/bounding/BoundingShape.hpp"
class Entity;
#include "src/omicron/entity/Entity.hpp"

namespace omi {

/******************************************\
| Contains an entity and a collision group |
\******************************************/
struct CollisionData {
    void* entity;
    std::string group;
};

/******************************************************************\
| Component used for detecting collisions between bounding shapes. |
\******************************************************************/
class CollisionDetector : public Physics {
public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // TODO: should this be public, could just have getter
    // the boundings within this
    std::vector<std::unique_ptr<BoundingShape>> m_boundings;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new collision detector with no initial bounding shapes
    @param id the identifier of the component
    @param group the collision group of this detector
    @param owner the entity this is owned by*/
    CollisionDetector(
            const std::string& id,
            const std::string& group,
                  void*      owner );

    /** Creates a new collision detector
    @param id the identifier of the component
    @param group the collision group of this detector
    @param boundings a list of boundings to be used by this detector
    @param owner the entity this is owned by*/
    CollisionDetector(
            const std::string&                 id,
            const std::string&                 group,
            const std::vector<BoundingShape*>& boundings,
                  void*                      owner );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual component::Type getType() const
    {
        return component::COLLISION;
    }

    /** Adds a bounding shape to this
    @param bounding a new bounding shape to add */
    void addBounding( BoundingShape* bounding );

    // TODO: remove bounding

    /** @return the physics group of this */
    const std::string& getGroup() const;

    void setGroup( const std::string& group );

    /** @return the entity that owns this component */
    Entity* getOwner();

    /** @return the collision data from this frame */
    std::vector<CollisionData>& getCollisionData();

    /** #Hidden
    Clears the collision data */
    void clearData();

    /** #Hidden
    Alerts this of a collision that has occurred with an entity from a group
    @param entity the entity the collision occured with
    @param group the collision group the entity was from */
    void detected( Entity* entity, const std::string& group );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the owner of this component
    Entity* m_owner;
    // the group of this detector
    std::string m_group;
    // the list of collisions this frame
    std::vector<CollisionData> m_collisionData;
};

} // namespace omi

#endif
