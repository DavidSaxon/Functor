#ifndef HERETIC_SCENES_STARTUPSCENE_H_
#   define HERETIC_SCENES_STARTUPSCENE_H_

#include "src/omicron/scene/Scene.hpp"

#include "src/entities/start_up/OmicronLogo.hpp"
#include "src/scenes/loading/LoadingScene.hpp"

/*************************************************************\
| Loads the initial resources and displays start up graphics. |
\*************************************************************/
class StartUpScene : public omi::Scene {
public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual void init();

    /** #Override */
    virtual bool update();

    /** #Override */
    virtual omi::Scene* nextScene();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the omicron cinematic
    OmicronLogo* m_omicronLogo;
};

#endif
