#include "Scene.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool Scene::execute() {

    // clear dirty components from the last iteration
    newComponents.clear();
    removeComponents.clear();

    // update this scene and store whether it's complete
    bool complete = update();

    // update all the entities
    updateEntities();

    return complete;
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Scene::addEntity(Entity* entity) {

    // initialise the entity
    entity->init();

    // TODO: check that the entity doesn't already exists in the scene

    // add to the list of all entities in the scene
    m_entities.push_back(t_EntityPtr(entity));
}

bool Scene::removeEntity(Entity* entity) {

    // TODO: should this exists?? (probably)
    // TODO: implement
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Scene::updateEntities() {

    // find all the new entities and remove entities marked for removal
    std::vector<Entity*> newEntities;
    for (t_EntityList::iterator it = m_entities.begin();
         it != m_entities.end();) {

        // get all new entities created by this entity
        for (std::vector<Entity*>::iterator itn = (*it)->getAddList().begin();
             itn != (*it)->getAddList().end(); ++itn) {

            newEntities.push_back(*itn);
        }
        // clear the entities new entities
        (*it)->getAddList().clear();

        //remove this entity
        if ((*it)->shouldRemove()) {

            // remove from the list which will erase all memory since
            // the entity is contained with a shared pointer
            it = m_entities.erase(it);
        }
        else {

            ++it;
        }
    }

    // copy the new entities into the list of all entities and initialise them
    for (std::vector<Entity*>::iterator it = newEntities.begin();
         it != newEntities.end(); ++it) {

        (*it)->init();
        m_entities.push_back(t_EntityPtr(*it));
    }

    // iterate over all the existing entities in the scene and update them
    // and collect all dirty components
    for (t_EntityList::iterator it = m_entities.begin();
         it != m_entities.end(); ++it) {

        (*it)->update();

        // find new components
        for (std::vector<Component*>::iterator itc =
            (*it)->getComponents().newComponents.begin();
            itc != (*it)->getComponents().newComponents.end(); ++itc) {

            newComponents.insert(*itc);
        }
        (*it)->getComponents().newComponents.clear();

        // find components to be removed
        if ((*it)->shouldRemove()) {

            (*it)->getComponents().copyToList(removeComponents);
        }
    }
}

} // namespace omi
