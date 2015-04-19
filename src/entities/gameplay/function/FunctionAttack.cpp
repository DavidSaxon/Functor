#include "FunctionAttack.hpp"

#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

FunctionAttack::FunctionAttack(
        const glm::vec3& colour,
        World* world,
        const glm::vec3& rotation,
        const glm::vec3& shitFuck,
        Function* function )
    :
    m_colour  ( colour ),
    m_world   ( world ),
    m_rotation( rotation ),
    m_shitFuck( shitFuck ),
    m_function( function ),
    m_distance( 7.0f ),
    m_exploded( false ),
    m_timer   ( 0.0f )
{
    // TODO: get contact distance
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FunctionAttack::init()
{
    omi::Transform* centerT = new omi::Transform(
            "",
            m_world->getPosition(),
            glm::vec3( 0.0f, 0.0f, 0.0f ),
            glm::vec3( 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( centerT );

    // trail
    m_trailPos = new omi::Transform(
            "",
            centerT,
            m_rotation * m_distance,
            glm::vec3( 0.0f, m_shitFuck.y, 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_trailPos );
    omi::Transform* stackRot = new omi::Transform(
            "",
            m_trailPos,
            glm::vec3(),
            glm::vec3( m_shitFuck.x, 0.0f, 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( stackRot );


    m_trailMesh =
            omi::ResourceManager::getMesh( "function_trail", "", stackRot );
    m_trailMesh->getMaterial().glow = new omi::Glow( m_colour, 0.4f );
    m_components.add( m_trailMesh );


    // explosion
    m_explosionPos = new omi::Transform(
            "",
            centerT,
            m_rotation,
            glm::vec3(),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_explosionPos );

    m_explosionMesh = omi::ResourceManager::getKeyFrameMesh(
            "function_explosion", "", m_explosionPos );
    m_explosionMesh->getMaterial().glow = new omi::Glow( m_colour, 0.2f );


    // play sound
    omi::SoundPool::play(
            omi::ResourceManager::getSound( "fire_1" ),
            false,
            0.6f
    );
}

void FunctionAttack::update()
{
    // move the trail in
    m_distance -= 0.2f * omi::fpsManager.getTimeScale();
    m_trailPos->translation = m_rotation * m_distance;

    // check if we've reached the surface
    if ( m_distance < 1.0f && !m_exploded )
    {
        m_exploded = true;
        m_components.add( m_explosionMesh );
        addEntity( m_function );
        omi::SoundPool::play(
                omi::ResourceManager::getSound( "explode_1" ),
                false,
                0.7f
        );
    }
    if ( m_distance < 0.0f )
    {
        m_trailMesh->visible = false;
    }

    // time out
    if ( m_exploded )
    {
        m_timer += 0.028f * omi::fpsManager.getTimeScale();
        if ( m_timer >= 1.0f)
        {
            remove();
        }
    }
}