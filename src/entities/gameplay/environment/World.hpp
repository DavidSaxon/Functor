#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_WORLD_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_WORLD_HPP_

#include "src/omicron/entity/Entity.hpp"

class World : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    World();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void init();

    /** #Override */
    void update();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the geometry of the world
    omi::Geometry* m_worldGeo;
    // a copy of the geo's originals vertices
    std::vector<glm::vec3> m_orgVert;
    // the geo's direction vectors
    std::vector<glm::vec3> m_dirVects;
    // indices of vertices which are technically the same vertex
    std::map<std::string, std::vector<unsigned>> m_vertHash;

    // time variable used for functions
    float m_time;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // reads the geo into the has map
    void initRead();
};

#endif
