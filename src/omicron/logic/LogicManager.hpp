#ifndef OMICRON_LOGIC_LOGICMANAGER_H_
#   define OMICRON_LOGIC_LOGICMANAGER_H_

#include <memory>

#include "lib/Utilitron/MacroUtil.hpp"

#include "src/omicron/component/updatable/Updatable.hpp"
#include "src/omicron/scene/Scene.hpp"

namespace omi {

/**********************************************************************\
| Handles the FPS manager, the execution of the current scene, and the |
| changing of scenes.                                                  |
\**********************************************************************/
class LogicManager {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN(LogicManager);

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new Logic Manager
    @param initScene the initial scene to begin executing */
    LogicManager(Scene* initScene);

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~LogicManager();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Perfroms an execution cycle of logic
    @return if components should be clear for the next scene */
    bool execute();

    /** @return the new components from the scene */
    std::set<Component*>& getNewComponents();

    /** @return the components to be removed from the scene */
    std::vector<Component*>& getRemoveComponents();

    /** @param updatable a new updatable component to manage */
    void addUpdatable(Updatable* updatable);

    /** @param updatable an updatable component to remove */
    void removeUpdatable(Updatable* updatable);

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // is true if we need to set up the scene
    bool m_sceneInit;
    // the current scene
    std::unique_ptr<Scene> m_scene;
    // the components to update
    std::vector<Updatable*> m_components;
};

} // namespace omi

#endif
