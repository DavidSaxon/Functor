#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_COSINEFUNCTION_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_COSINEFUNCTION_HPP_

#include "Function.hpp"

class CosineFunc : public Function
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    CosineFunc( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void apply( const glm::vec3& dirVect, glm::vec3& effect );
};

#endif
