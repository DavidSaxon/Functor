#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_RANDFUNCTION_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_RANDFUNCTION_HPP_

#include "Function.hpp"

class RandFunc : public Function
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    RandFunc( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void apply( const glm::vec3& dirVect, glm::vec3& effect );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    int m_seedation;
};

#endif
