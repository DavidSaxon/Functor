#ifndef HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_WORLD_HPP_
#   define HERETIC_ENTITIES_GAMEPLAY_ENVIRONMENT_WORLD_HPP_

#include "src/omicron/entity/Entity.hpp"

class World : public omi::Entity
{
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    World(
            float rotationSpeed,
            float sunDistance,
            float orbitSpeed,
            const std::string& orbitMeshId );

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

    // the speed at which the planet rotates
    float m_rotationSpeed;
    // the distance of the world from the sun
    float m_sunDistance;
    // the speed of the planet's orbit
    float m_orbitSpeed;
    // the resource name of the mesh to use for showing orbit
    std::string m_orbitMeshId;

    // the rotation point of the world ( 0, 0, 0 )
    omi::Transform* m_rotPoint;
    // the position of the planet
    omi::Transform* m_position;

    // the mesh of the planet's orbit
    omi::Mesh* m_orbitMesh;

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
