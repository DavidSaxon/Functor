#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_TOWERBASE_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_TOWERBASE_HPP_

#include "src/omicron/entity/Entity.hpp"

class Tower;

//------------------------------------------------------------------------------
//                              FORWARD DECLARATIONS
//------------------------------------------------------------------------------

class World;

class TowerBase : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    TowerBase( World* world, const glm::vec3& rotation );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    World* m_world;
    glm::vec3 m_rotation;
    glm::vec3 m_dirVect;

    omi::Transform* m_pos;

    std::vector<Tower*> m_blocks;

    unsigned m_heightCacheId;
};

#endif
