#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_EVIRONMENT_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_EVIRONMENT_HPP_

#include "src/omicron/entity/Entity.hpp"

class Environment : public omi::Entity
{
    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();
};

#endif
