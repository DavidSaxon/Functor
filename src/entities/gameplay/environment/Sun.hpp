#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_SUN_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_SUN_HPP_

#include "src/omicron/entity/Entity.hpp"

class Sun : public omi::Entity
{
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
