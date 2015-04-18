#include "World.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "src/data/Globals.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void World::init()
{
    // add the mesh
    omi::Mesh* worldMesh =
            omi::ResourceManager::getMesh( "world_std", "", NULL );
    m_components.add( worldMesh );

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

    // random jitter test
    std::map<std::string, std::vector<unsigned>>::iterator it;
    for ( it = m_vertHash.begin(); it != m_vertHash.end(); ++it )
    {
        float rx = static_cast<float>( rand()  % 1000 ) / 1000.0f;
        rx -= 0.5f;
        rx *= 0.01f;
        float ry = static_cast<float>( rand()  % 1000 ) / 1000.0f;
        ry -= 0.5f;
        ry *= 0.01f;
        float rz = static_cast<float>( rand()  % 1000 ) / 1000.0f;
        rz -= 0.5f;
        rz *= 0.01f;

        std::vector<unsigned>::iterator itv;
        for ( itv = it->second.begin(); itv != it->second.end(); ++itv )
        {
            m_worldGeo->vertices[ *itv ].x += rx;
            m_worldGeo->vertices[ *itv ].y += ry;
            m_worldGeo->vertices[ *itv ].z += rz;
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
