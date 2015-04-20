#ifndef HERETIC_ENTITIES_GAMEPLAY_FUNCTION_FUNCTION_ATTACK_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_FUNCTION_FUNCTION_ATTACK_HPP_

#include "src/omicron/entity/Entity.hpp"

#include "src/entities/gameplay/function/Function.hpp"

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class World;

class FunctionAttack : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    FunctionAttack(
            const glm::vec3& colour,
            World* world,
            const glm::vec3& rotation,
            const glm::vec3& shitFuck,
            Function* function );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    glm::vec3 m_colour;
    World* m_world;
    glm::vec3 m_rotation;
    glm::vec3 m_shitFuck;
    Function* m_function;

    float m_contactDis;
    float m_distance;
    bool m_exploded;
    float m_timer;

    omi::Transform* m_trailPos;
    omi::Transform* m_explosionPos;

    omi::Mesh* m_trailMesh;
    omi::Mesh* m_explosionMesh;
};

#endif
