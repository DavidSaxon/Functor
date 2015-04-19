#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_SINEFUNCTION_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_SINEFUNCTION_HPP_

#include "Function.hpp"

class SineFunc : public Function
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    SineFunc( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void apply( const glm::vec3& dirVect, glm::vec3& effect );
};

#endif
