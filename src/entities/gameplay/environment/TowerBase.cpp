#include "TowerBase.hpp"

#include "src/entities/gameplay/environment/Tower.hpp"
#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TowerBase::TowerBase( World* world, const glm::vec3& rotation )
    :
    m_world   ( world ),
    m_rotation( rotation )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TowerBase::init()
{
    // calculate the direction vector
    glm::mat4 rotMatrix( 1.0f );
    rotMatrix *= glm::rotate(
            m_rotation.y * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 0.0f, 1.0f, 0.0f )
    );
    rotMatrix *= glm::rotate(
            m_rotation.x * util::math::DEGREES_TO_RADIANS,
            glm::vec3( 1.0f, 0.0f, 0.0f )
    );
    rotMatrix *= glm::translate( glm::vec3( 0.0f, 0.0f, 1.0f ) );

    glm::vec4 dir4( 0.0f, 0.0f, 0.0f, 1.0f );
    dir4 = rotMatrix * dir4;
    m_dirVect = glm::normalize( dir4.xyz() );

    // m_dirVect = glm::vec3( 0.0f, 0.0f, 1.0f );

    m_pos = new omi::Transform(
            "",
            m_world->getPosition(),
            m_dirVect,
            glm::vec3( 0.0f, m_rotation.y, 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_pos );
    omi::Transform* stackRot = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( m_rotation.x, 0.0f, 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( stackRot );

    Tower* t = new Tower( stackRot, 0.0f );
    m_blocks.push_back( t );
    addEntity( t );

    // register in cache
    m_heightCacheId = m_world->addHeightMapCache( m_dirVect );
}

void TowerBase::update()
{
    // TODO: timer

    // TODO: build

    // TODO: check bottom

    // make sure is setting on the bottom
    m_pos->translation =
            m_dirVect * m_world->resolveHeightMapCache( m_heightCacheId );
}
