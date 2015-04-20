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

    TowerBase( World* world, const glm::vec3& rotation, float timeout = 0.0f );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void init();

    void update();

    void start();

    void stop();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    World* m_world;
    glm::vec3 m_rotation;
    glm::vec3 m_dirVect;

    omi::Transform* m_pos;
    omi::Transform* m_stackRot;

    omi::Mesh* m_mesh;

    std::vector<Tower*> m_blocks;

    unsigned m_heightCacheId;

    float m_startTimer;
    float m_timeOut;
    float m_nextBlockTimer;

    float m_currentLevel;

    float m_baseHeight;
    float m_height;

    bool m_started;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    void build();

    void destroy();
};

#endif
