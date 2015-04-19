#include "Tower.hpp"

#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Tower::Tower( omi::Transform* parentPos, float height )
    :
    m_parentPos( parentPos ),
    m_height   ( height )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Tower::init()
{
    m_pos = new omi::Transform(
            "",
            m_parentPos,
            glm::vec3(), // TODO: height y
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_pos );

    m_mesh1 = omi::ResourceManager::getMesh( "tower1", "", m_pos );
    m_components.add( m_mesh1 );
    m_mesh2 = omi::ResourceManager::getMesh( "tower2", "", m_pos );
    m_components.add( m_mesh2 );
    m_mesh3 = omi::ResourceManager::getMesh( "tower3", "", m_pos );
    m_components.add( m_mesh3 );
}

void Tower::update()
{

}
