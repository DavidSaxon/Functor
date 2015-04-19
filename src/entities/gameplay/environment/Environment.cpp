#include "Environment.hpp"

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Environment::init()
{
    // add star light
    omi::Transform* dir1 = new omi::Transform(
                "",
                glm::vec3( -1.0f, 0.5f, 0.0f ),
                glm::vec3(),
                glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( dir1 );
    omi::DirectionalLight* light1 = new omi::DirectionalLight(
            "", dir1, 0.35f, glm::vec3( 0.9f, 0.9f, 1.0f )
    );
    m_components.add( light1 );


    omi::Transform* dir2 = new omi::Transform(
                "",
                glm::vec3( 1.0f, -0.5f, 0.0f ),
                glm::vec3(),
                glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( dir2 );
    omi::DirectionalLight* light2 = new omi::DirectionalLight(
            "", dir2, 0.35f, glm::vec3( 0.9f, 0.9f, 1.0f )
    );
    m_components.add( light2 );
}

void Environment::update()
{
}
