#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_SUBFUNC_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_SUBFUNC_HPP_

#include "Function.hpp"

class SubFunc : public Function
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    SubFunc( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void apply( const glm::vec3& dirVect, glm::vec3& effect );
};

#endif
