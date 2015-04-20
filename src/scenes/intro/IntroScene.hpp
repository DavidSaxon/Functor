#ifndef HERETIC_SCENES_INTROSCENE_HPP_
#   define HERETIC_SCENES_INTROSCENE_HPP_

#include "src/omicron/scene/Scene.hpp"

#include "src/entities/intro_e/IntroControl.hpp"

class IntroScene : public omi::Scene {
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

    IntroControl* introC;
};

#endif
