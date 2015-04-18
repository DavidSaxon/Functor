#include "CollisionDetect.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

std::vector<CollisionDetector*> CollisionDetect::m_detectors;
std::vector<CheckPair> CollisionDetect::m_check;
std::map<std::string, std::vector<CollisionDetector*>>
        CollisionDetect::m_groups;

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void CollisionDetect::checkGroup( const std::string& a, const std::string& b )
{
    // TODO: check pair doesn't already exists
    CheckPair pair;
    pair.a = a;
    pair.b = b;
    m_check.push_back( pair );
}

void CollisionDetect::update()
{
    // sort the collision detectors into their groups
    m_groups.clear();
    for ( std::vector<CollisionDetector*>::iterator detector =
         m_detectors.begin(); detector != m_detectors.end(); ++detector )
    {
        ( *detector )->clearData();
        // sort into a map
        std::string group = ( *detector )->getGroup();
        // if the group doesn't already exist create it
        if ( m_groups.find( group ) == m_groups.end() )
        {
            m_groups.insert(
                std::make_pair( group, std::vector<CollisionDetector*>() ) );
        }
        m_groups[group].push_back( *detector );
    }

    // go over each check pair
    for ( std::vector<CheckPair>::iterator it = m_check.begin();
         it != m_check.end(); ++it ) {

        // go over each item in the first group
        for ( std::vector<CollisionDetector*>::iterator first =
            m_groups[it->a].begin();
            first != m_groups[it->a].end(); ++first )
        {
            // go over each item in the second m_groups
            for ( std::vector<CollisionDetector*>::iterator second =
                m_groups[it->b].begin();
                second != m_groups[it->b].end(); ++second )
            {
                // perform collision detection
                if ( first != second )
                {
                    processDetectors( *first, *second );
                }
            }
        }
    }
}

void CollisionDetect::addDetector( CollisionDetector* detector )
{
    m_detectors.push_back(detector);
}

void CollisionDetect::removeDetector( CollisionDetector* detector )
{
    for ( std::vector<CollisionDetector*>::iterator it = m_detectors.begin();
         it != m_detectors.end(); )
    {
        if ( *it == detector )
        {
            it = m_detectors.erase( it );
        }
        else
        {
            ++it;
        }
    }
}

void CollisionDetect::clear()
{
    m_detectors.clear();
    m_check.clear();
}

const std::vector<BoundingShape*> CollisionDetect::checkAgainstGroup(
        BoundingShape* bounding,
        const std::string& group )
{
    // the list of boundings collisions are occurring with
    std::vector<BoundingShape*> collisions;

    // iterate over detectors in the group
    for ( std::vector<CollisionDetector*>::iterator detector =
          m_groups[group].begin(); detector != m_groups[group].end();
          ++detector )
    {
        // iterate over the boundings in the detector
        for ( std::vector<std::unique_ptr<BoundingShape>>::iterator bd =
             (*detector)->m_boundings.begin();
             bd != (*detector)->m_boundings.end(); ++bd )
        {
            // check collision
            if ( checkCollision( bounding, bd->get() ) )
            {
                // a collision was found, record it in the list
                collisions.push_back( bd->get() );
            }
        }
    }

    return collisions;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void CollisionDetect::processDetectors(
    CollisionDetector* a, CollisionDetector* b )
{
    // iterate over each bounding in the first detector
    for ( std::vector<std::unique_ptr<BoundingShape>>::iterator first =
         a->m_boundings.begin(); first != a->m_boundings.end(); ++first )
    {
        // iterate over each bounding in the second detector
        for ( std::vector<std::unique_ptr<BoundingShape>>::iterator second =
            b->m_boundings.begin(); second != b->m_boundings.end(); ++second )
        {
            // check if the boundings are touching
            if ( checkCollision( first->get(), second->get() ) )
            {
                // pass data back to the detector
                a->detected( b->getOwner(), b->getGroup() );
            }
        }
    }
}

bool CollisionDetect::checkCollision( BoundingShape* a, BoundingShape* b )
{
    if ( a->getType() == bounding::CIRCLE &&
         b->getType() == bounding::CIRCLE )
    {
        return checkCircleCircle(
            dynamic_cast<BoundingCircle*>( a ),
            dynamic_cast<BoundingCircle*>( b )
        );
    }
    else if ( a->getType() == bounding::RECTANGLE &&
              b->getType() == bounding::RECTANGLE )
    {
        return checkRectRect(
            dynamic_cast<BoundingRect*>( a ),
            dynamic_cast<BoundingRect*>( b )
        );
    }
    else if ( a->getType() == bounding::SPHERE &&
              b->getType() == bounding::SPHERE )
    {
        return checkSphereSphere(
            dynamic_cast<BoundingSphere*>( a ),
            dynamic_cast<BoundingSphere*>( b )
        );
    }

    std::cout << "ERROR: unrecognised collision type" << std::endl;
    return false;
}

bool CollisionDetect::checkCircleCircle( BoundingCircle* a, BoundingCircle* b )
{
    // TODO: scaling
    glm::vec2 aPos = ( a->getTransform()->translation + a->getOffset() ).xz();
    glm::vec2 bPos = ( b->getTransform()->translation + b->getOffset() ).xz();
    // check if circles are colliding
    float distance = glm::distance( aPos, bPos );

    return distance <= a->getRadius() + b->getRadius();
}

bool CollisionDetect::checkRectRect( BoundingRect* a, BoundingRect* b )
{
    // TODO: rotation
    // TODO: scaling
    glm::vec2 aPos = ( a->getTransform()->translation + a->getOffset() ).xz();
    glm::vec2 bPos = ( b->getTransform()->translation + b->getOffset() ).xz();

    // short-hand
    float a1x = aPos.x - ( a->getSize().x / 2.0f );
    float a2x = aPos.x + ( a->getSize().x / 2.0f );
    float a1y = aPos.y - ( a->getSize().y / 2.0f );
    float a2y = aPos.y + ( a->getSize().y / 2.0f );
    float b1x = bPos.x - ( b->getSize().x / 2.0f );
    float b2x = bPos.x + ( b->getSize().x / 2.0f );
    float b1y = bPos.y - ( b->getSize().y / 2.0f );
    float b2y = bPos.y + ( b->getSize().y / 2.0f );

    return
        a1x < b2x &&
        a2x > b1x &&
        a1y < b2y &&
        a2y > b1y;
}

bool CollisionDetect::checkSphereSphere( BoundingSphere* a, BoundingSphere* b )
{
    // TODO: scaling
    glm::vec3 aPos = a->getTransform()->translation + a->getOffset();
    glm::vec3 bPos = b->getTransform()->translation + b->getOffset();
    // check if circles are colliding
    float distance = glm::distance( aPos, bPos );

    return distance <= a->getRadius() + b->getRadius();
}

} // namespace omi
