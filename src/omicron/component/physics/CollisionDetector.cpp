#include "CollisionDetector.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

CollisionDetector::CollisionDetector(
        const std::string& id,
        const std::string& group,
              void*      owner ) :
    Physics( id ),
    m_group( group ),
    m_owner( static_cast<Entity*>( owner ) )
{
}

CollisionDetector::CollisionDetector(
        const std::string& id,
        const std::string& group,
        const std::vector<BoundingShape*>& boundings,
              void*      owner ) :
    Physics( id ),
    m_group( group ),
    m_owner( static_cast<Entity*>( owner ) )
{
    // copy the boundings into a new vector of smart pointers
    for ( std::vector<BoundingShape*>::const_iterator it = boundings.begin();
         it != boundings.end(); ++it )
    {
        m_boundings.push_back( std::unique_ptr<BoundingShape>( *it ) );
    }
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void CollisionDetector::addBounding( BoundingShape* bounding )
{
    m_boundings.push_back( std::unique_ptr<BoundingShape>( bounding ) );
}

const std::string& CollisionDetector::getGroup() const
{
    return m_group;
}

void CollisionDetector::setGroup( const std::string& group )
{
    m_group = group;
}

Entity* CollisionDetector::getOwner()
{
    return m_owner;
}

std::vector<CollisionData>& CollisionDetector::getCollisionData()
{
    return m_collisionData;
}

void CollisionDetector::clearData()
{
    m_collisionData.clear();
}

void CollisionDetector::detected( Entity* entity, const std::string& group )
{
    CollisionData data;
    data.entity = entity;
    data.group  = group;
    m_collisionData.push_back( data );
}

} // namespace omi
