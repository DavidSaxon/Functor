#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_FUNCTION_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_FUNCTION_HPP_

#include "src/omicron/entity/Entity.hpp"

class Function : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    Function( const glm::vec3& focalPoint, float power, float distance );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

    bool isDone();

    void fuckOff();

    virtual void apply( const glm::vec3& dirVect, glm::vec3& effect ) = 0;

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the focal point of the function
    glm::vec3 m_focalPoint;
    // the power of the function
    float m_power;
    // the current distance of the functions
    float m_currentDistance;
    // the max distance of the function
    float m_maxDistance;
};

#endif
