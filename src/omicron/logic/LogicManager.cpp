#include  "LogicManager.hpp"

#include <iostream>

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

LogicManager::LogicManager(Scene* initScene) :
    m_sceneInit(true),
    m_scene(initScene) {
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

LogicManager::~LogicManager() {
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

bool LogicManager::execute() {

    // initialise a new scene
    if (m_sceneInit) {

        m_scene->init();
        fpsManager.zero();
        m_sceneInit = false;
    }

    // update the fps manager
    fpsManager.update();

    // execute the current scene
    if ( m_scene->execute() )
    {
        // get the next scene
        m_scene = std::unique_ptr<Scene>(m_scene->nextScene());

        // clear the components of this scene
        //if the scene we get is null we're done
        if (!m_scene)
        {
            omi_running = false;
            return true;
        }
        m_sceneInit = true;
        return true;
    } else {

        // update components
        for (std::vector<Updatable*>::iterator it = m_components.begin();
             it != m_components.end(); ++it) {

            (*it)->update();
        }
    }

    return false;
}

std::set<Component*>& LogicManager::getNewComponents() {

    return m_scene->newComponents;
}

std::vector<Component*>& LogicManager::getRemoveComponents() {

    return m_scene->removeComponents;
}

void LogicManager::addUpdatable(Updatable* updatable) {

    m_components.push_back(updatable);
}

void LogicManager::removeUpdatable(Updatable* updatable) {

    // search and remove updatable
    for (std::vector<Updatable*>::iterator it = m_components.begin();
         it != m_components.end(); ++it) {

        if (*it == updatable) {

            it = m_components.erase(it);
        }
        else {

            ++it;
        }
    }
}

} // namespace omi
