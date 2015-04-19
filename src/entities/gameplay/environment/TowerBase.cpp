#include "TowerBase.hpp"

#include "src/entities/gameplay/environment/Tower.hpp"
#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TowerBase::TowerBase( World* world, const glm::vec3& dirVect )
    :
    m_world  ( world ),
    m_dirVect( dirVect )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TowerBase::init()
{
    // TODO: dir vec from rotation instead?

    m_pos = new omi::Transform(
            "",
            m_world->getPosition(),
            m_dirVect,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_pos );

    Tower* t = new Tower( m_pos, 0.0f );
    m_blocks.push_back( t );
    addEntity( t );
}

void TowerBase::update()
{
    // TODO: timer

    // TODO: build

    // TODO: check bottom

    // make sure is setting on the bottom
    m_pos->translation = m_dirVect * m_world->getHeightMapPos( m_dirVect );
}
