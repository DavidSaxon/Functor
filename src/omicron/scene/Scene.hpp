#ifndef OMICRON_SCENE_SCENE_H_
#   define OMICRON_SCENE_SCENE_H_

#include <memory>
#include <set>
#include <vector>

#include "src/omicron/Omicron.hpp"
#include "src/omicron/entity/Entity.hpp"
#include "src/omicron/physics/collision_detect/CollisionDetect.hpp"
#include "src/omicron/resource/ResourceManager.hpp"

namespace omi {

//-----------------------------------TYPEDEFS-----------------------------------

typedef std::unique_ptr<Entity> t_EntityPtr;
typedef std::vector<t_EntityPtr>  t_EntityList;

/*********************************************\
| Abstract base class that all scenes extend. |
\*********************************************/
class Scene {
public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // TODO: why is this a set NO!
    // the set of new components
    std::set<Component*> newComponents;
    // the list of components to be removed
    std::vector<Component*> removeComponents;

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~Scene() {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Initialises the scene */
    virtual void init() = 0;

    /** #Hidden
    Controls execution of the scene */
    bool execute();

    /** performs a logic cycle of the scene
    @return if true the scene is complete and next scene should begin */
    virtual bool update() = 0;

    /** @return the next scene to be executed */
    virtual Scene* nextScene() = 0;

    // TODO: input

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Adds a new entity
    #NOTE: the scene will hold ownership of the entity pointer
    @param entity the new entity to add */
    void addEntity(Entity* entity);

    /** Removes an entity if it exists within the scene
    #NOTE: the pointer to the entity will be deleted
    @param entity the entity to remove
    @return whether or not the entity existed within the scene and was
    therefore removed */
    bool removeEntity(Entity* entity);

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the list of entities
    t_EntityList m_entities;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Updates all entities in the entity list */
    void updateEntities();
};

} // namespace omi

#endif
