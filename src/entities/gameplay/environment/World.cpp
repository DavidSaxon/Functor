#include "World.hpp"

#include <iomanip>
#include <iostream>
#include <sstream>

#include "src/data/Globals.hpp"

#include "src/entities/gameplay/environment/TowerBase.hpp"

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
    m_orbitMeshId  ( orbitMeshId )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void World::init()
{
    // randomly generate rotation
    float rot = static_cast<float>( ( rand() % 1000 ) / 1000.0f ) * 360.0f;

    // the position of the world
    m_rotPoint = new omi::Transform(
        "",
        glm::vec3(),
        glm::vec3(0.0f, rot, 0.0f ),
        glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_position = new omi::Transform(
            "",
            m_rotPoint,
            glm::vec3( 0.0f, 0.0f, m_sunDistance ),
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );

    // add the mesh
    omi::Mesh* worldMesh =
            omi::ResourceManager::getMesh( "world_std", "", m_position );
    worldMesh->giveUniqueGeo();
    m_components.add( worldMesh );

    // add the orbit mesh
    m_orbitMesh =
            omi::ResourceManager::getMesh( m_orbitMeshId, "", NULL );
    m_components.add( m_orbitMesh );

    // store the geo list pointer
    m_worldGeo = worldMesh->getGeometry();

    // read the geo
    initRead();

    addEntity( new TowerBase(
            this, glm::vec3( 0.0f, 0.0f, 0.0f ) ) );
}

void World::update()
{
    // skip if omicron is paused
    if ( global::pause )
    {
        return;
    }

    // rotate
    m_position->rotation.y += m_rotationSpeed * omi::fpsManager.getTimeScale();

    // orbit
    m_rotPoint->rotation.y += m_orbitSpeed * omi::fpsManager.getTimeScale();

    // show orbit?
    if ( global::m_inOrbit )
    {
        m_orbitMesh->visible = false;
    }
    else
    {
        m_orbitMesh->visible = true;
    }

    // iterate over the geometry to apply functions
    std::map<std::string, std::vector<unsigned>>::iterator it;
    for ( it = m_vertHash.begin(); it != m_vertHash.end(); ++it )
    {
        std::vector<unsigned>::iterator itv;
        for ( itv = it->second.begin(); itv != it->second.end(); ++itv )
        {
            glm::vec3 effect;
            glm::vec3 finalEffect;
            std::vector<Function*>::iterator itf;
            for ( itf = m_functions.begin(); itf != m_functions.end(); ++itf )
            {
                glm::vec3 funcEffect;
                ( *itf )->apply( m_dirVects[ *itv ], funcEffect );

                if ( ( *itf )->isDone() )
                {
                    finalEffect += funcEffect;
                }
                else
                {
                    effect += funcEffect;
                }
            }

            // apply
            m_orgVert[ *itv ] = m_orgVert[ *itv ] + finalEffect;
            m_worldGeo->vertices[ *itv ] = m_orgVert[ *itv ] + effect;
        }
    }

    // remove complete functions
    std::vector<Function*>::iterator itf;
    for ( itf = m_functions.begin(); itf != m_functions.end(); )
    {
        if ( ( ( *itf )->isDone() ) )
        {
            ( *itf )->fuckOff();
            itf = m_functions.erase( itf );
        }
        else
        {
            ++itf;
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

omi::Transform* World::getRotPoint()
{
    return m_rotPoint;
}

omi::Transform* World::getPosition()
{
    return m_position;
}

float World::getDistance() const
{
    return m_sunDistance;
}

void World::addFunction( Function* func )
{
    m_functions.push_back( func );
}

float World::getHeightMapPos( const glm::vec3& dirVect )
{
    // find the three closet points
    int closet1 = -1;
    float closetDis1 = 1000.0f;
    int closet2 = -1;
    float closetDis2 = 1000.0f;
    int closet3 = -1;
    float closetDis3 = 1000.0f;

    for ( unsigned i = 0; i < m_dirVects.size(); ++i )
    {
        float d = fabs( glm::distance( dirVect, m_dirVects[ i ] ) );

        if ( d < closetDis1 )
        {
            closet1 = i;
            closetDis1 = d;
        }
        else if ( d < closetDis2 )
        {
            closet2 = i;
            closetDis2 = d;
        }

        else if ( d < closetDis3 )
        {
            closet3 = i;
            closetDis3 = d;
        }
    }

    // get average
    float height =
        fabs( glm::distance( m_worldGeo->vertices[ closet1 ], glm::vec3() ) ) +
        fabs( glm::distance( m_worldGeo->vertices[ closet2 ], glm::vec3() ) ) +
        fabs( glm::distance( m_worldGeo->vertices[ closet3 ], glm::vec3() ) );

    return height / 3.0f;
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
            m_keyVerts.push_back( m_worldGeo->vertices[ i ] );
            m_vertHash[ ss.str() ] = std::vector<unsigned>();
        }
        m_vertHash[ ss.str() ].push_back( i );
    }
}
