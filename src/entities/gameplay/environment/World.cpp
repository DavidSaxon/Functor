#include "World.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

World::World(
        float rotationSpeed,
        float sunDistance,
        float orbitSpeed,
        const std::string& orbitMeshId )
    :
    m_rotationSpeed( rotationSpeed ),
    m_sunDistance  ( sunDistance ),
    m_orbitSpeed   ( orbitSpeed ),
    m_orbitMeshId  ( orbitMeshId ),
    m_time         ( 0.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void World::init()
{
    // the position of the world
    m_rotPoint = new omi::Transform(
        "",
        glm::vec3(),
        glm::vec3(),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_position = new omi::Transform(
            "",
            m_rotPoint,
            glm::vec3( -m_sunDistance, 0.0f, 0.0f ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );

    // add the mesh
    omi::Mesh* worldMesh =
            omi::ResourceManager::getMesh( "world_std", "", m_position );
    m_components.add( worldMesh );

    // add the orbit mesh
    omi::Mesh* orbitMesh =
            omi::ResourceManager::getMesh( m_orbitMeshId, "", NULL );
    m_components.add( orbitMesh );

    // store the geo list pointer
    m_worldGeo = worldMesh->getGeometry();

    // read the geo
    initRead();
}

void World::update()
{
    // skip if omicron is paused
    if ( global::pause )
    {
        return;
    }

    // increase time
    m_time += 0.005f * omi::fpsManager.getTimeScale();

    // rotate
    m_position->rotation.y += m_rotationSpeed * omi::fpsManager.getTimeScale();

    // orbit
    m_rotPoint->rotation.y += m_orbitSpeed * omi::fpsManager.getTimeScale();



    //---------------------------------FUNCTION---------------------------------


    // random jitter test
    // std::map<std::string, std::vector<unsigned>>::iterator it;
    // for ( it = m_vertHash.begin(); it != m_vertHash.end(); ++it )
    // {
    //     float rx = static_cast<float>( rand()  % 1000 ) / 1000.0f;
    //     rx -= 0.5f;
    //     rx *= 0.01f;
    //     float ry = static_cast<float>( rand()  % 1000 ) / 1000.0f;
    //     ry -= 0.5f;
    //     ry *= 0.01f;
    //     float rz = static_cast<float>( rand()  % 1000 ) / 1000.0f;
    //     rz -= 0.5f;
    //     rz *= 0.01f;

    //     std::vector<unsigned>::iterator itv;
    //     for ( itv = it->second.begin(); itv != it->second.end(); ++itv )
    //     {
    //         m_worldGeo->vertices[ *itv ].x += rx;
    //         m_worldGeo->vertices[ *itv ].y += ry;
    //         m_worldGeo->vertices[ *itv ].z += rz;
    //     }
    // }


    // central point of the ripple
    glm::vec3 focalPoint( 0.0f, 0.5, 1.0f );
    focalPoint = glm::normalize( focalPoint );

    // the power of the function
    float power = 0.05f;
    // the distance the the ripple can travel
    float maxDis = 1.0f;

    // sin test
    std::map<std::string, std::vector<unsigned>>::iterator it;
    for ( it = m_vertHash.begin(); it != m_vertHash.end(); ++it )
    {
        std::vector<unsigned>::iterator itv;
        for ( itv = it->second.begin(); itv != it->second.end(); ++itv )
        {
            // calculate the distance from the focal point
            float distance =
                    fabs( glm::distance( m_dirVects[ *itv ], focalPoint ) );

            glm::vec3 effect;
            if ( abs( distance ) < maxDis )
            {
                float funcResolve = static_cast<float>(
                    sin( ( distance - m_time ) * 20.0f ) *
                    ( ( maxDis - distance ) / maxDis )
                );

                effect.x = (  m_dirVects[ *itv ].x * funcResolve ) * power;
                effect.y = (  m_dirVects[ *itv ].y * funcResolve ) * power;
                effect.z = (  m_dirVects[ *itv ].z * funcResolve ) * power;
            }

            // apply
            m_worldGeo->vertices[ *itv ].x =
                    m_orgVert[ *itv ].x + effect.x;
            m_worldGeo->vertices[ *itv ].y =
                    m_orgVert[ *itv ].y + effect.y;
            m_worldGeo->vertices[ *itv ].z =
                    m_orgVert[ *itv ].z + effect.z;
        }
    }


    // recalculate normals
    for ( unsigned i = 0; i < m_worldGeo->vertices.size(); i += 3 )
    {
        glm::vec3 u = m_worldGeo->vertices[ i + 1 ] - m_worldGeo->vertices[ i ];
        glm::vec3 v = m_worldGeo->vertices[ i + 2 ] - m_worldGeo->vertices[ i ];

        glm::vec3 normal(
                ( u.y * v.z ) - ( u.z * v.y ),
                ( u.z * v.x ) - ( u.x * v.z ),
                ( u.x * v.y ) - ( u.y * v.x )
        );

        normal = glm::normalize( normal );

        m_worldGeo->normals[ i ]     = normal;
        m_worldGeo->normals[ i + 1 ] = normal;
        m_worldGeo->normals[ i + 2 ] = normal;
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void World::initRead()
{
    // store the originals
    m_orgVert = std::vector<glm::vec3>( m_worldGeo->vertices );

    // store directions vectors
    for ( unsigned i = 0; i < m_orgVert.size(); ++i )
    {
        m_dirVects.push_back( glm::normalize( m_orgVert[ i ] ) );
    }

    // sort the vectices and collect up duplicates
    std::vector<glm::vec3>::iterator it;
    for ( unsigned i = 0; i < m_worldGeo->vertices.size(); ++ i )
    {
        // hash the vertex
        std::stringstream ss;
        ss << std::setprecision( 3 ) << std::fixed;
        ss << m_worldGeo->vertices[ i ].x << ":";
        ss << m_worldGeo->vertices[ i ].y << ":";
        ss << m_worldGeo->vertices[ i ].z;

        if ( m_vertHash.find( ss.str() ) == m_vertHash.end() )
        {
            m_vertHash[ ss.str() ] = std::vector<unsigned>();
        }
        m_vertHash[ ss.str() ].push_back( i );
    }
}
