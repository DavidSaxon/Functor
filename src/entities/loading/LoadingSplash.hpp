#ifndef REVERIE_ENTITIES_LOADING_LOADINGSPLASH_HPP_
#   define REVERIE_ENTITIES_LOADING_LOADINGSPLASH_HPP_

#include "src/omicron/entity/Entity.hpp"

/***************************\
| Shows the loading screen. |
\***************************/
class LoadingSplash : public omi::Entity {
public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();
};

#endif
