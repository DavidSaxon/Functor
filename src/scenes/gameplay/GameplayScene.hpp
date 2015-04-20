#ifndef HERETIC_SCENES_GAMEPLAYSCENE_HPP_
#   define HERETIC_SCENES_GAMEPLAYSCENE_HPP_

#include "src/omicron/scene/Scene.hpp"

/****************************************************\
| The main scene of functor which controls game-play. |
\****************************************************/
class GameplayScene : public omi::Scene {
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
};

#endif
