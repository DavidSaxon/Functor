#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_ADDFUNC_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_ADDFUNC_HPP_

#include "Function.hpp"

class AddFunc : public Function
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    AddFunc( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void apply( const glm::vec3& dirVect, glm::vec3& effect );
};

#endif
