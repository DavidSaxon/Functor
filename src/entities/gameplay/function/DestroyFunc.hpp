#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_DESTROYFUNCTION_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_DESTROYFUNCTION_HPP_

#include "Function.hpp"

class DestroyFunc : public Function
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    DestroyFunc( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void update();

    bool isDone();

    void apply( const glm::vec3& dirVect, glm::vec3& effect );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    float m_time;
};

#endif
