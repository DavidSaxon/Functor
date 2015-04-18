#ifndef HERETIC_ENTITIES_DEBUG_FPSCOUNTER_HPP_
#   define HERETIC_ENTITIES_DEBUG_FPSCOUNTER_HPP_

#include "src/omicron/entity/Entity.hpp"

/************************************************************************\
| Renders the current frames per second to the upper right corner of the |
| screen.                                                                |
\************************************************************************/
class FPSCounter : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    FPSCounter();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the timer used so we don't update the text every frame
    float m_timer;
    // the text displaying the frames per second
    omi::Text* m_text;
};

#endif
