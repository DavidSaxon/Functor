#include "TowerBase.hpp"

#include "src/entities/gameplay/environment/Tower.hpp"
#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{
static const float BLOCK_HEIGHT = 0.05f;
static const float NEXT_BLOCK_EASY_SPEED = 0.0075f;
static const float NEXT_BLOCK_MEDIUM_SPEED = 0.01f;
static const float NEXT_BLOCK_HARD_SPEED = 0.0125f;
static const unsigned BUILD_EASY_PROB       = 75;
static const unsigned BUILD_MEDIUM_PROB     = 50;
static const unsigned BUILD_HARD_PROB       = 25;
static const unsigned STR_EASY_NORM         = 60;
static const unsigned STR_EASY_STNG         = 85;
static const unsigned STR_MEDI_NORM         = 50;
static const unsigned STR_MEDI_STNG         = 75;
static const unsigned STR_HARD_NORM         = 70;
static const unsigned STR_HARD_STNG         = 30;
} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TowerBase::TowerBase( World* world, const glm::vec3& rotation )
    :
    m_world         ( world ),
    m_rotation      ( rotation ),
    m_startTimer    ( 0.0f ),
    m_nextBlockTimer( 0.0f )
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
    m_stackRot = new omi::Transform(
            "",
            m_pos,
            glm::vec3(),
            glm::vec3( m_rotation.x, 0.0f, 0.0f ),
            glm::vec3( 1.0f, 1.0f, 1.0f )
    );
    m_components.add( m_stackRot );

    // register in cache
    m_heightCacheId = m_world->addHeightMapCache( m_dirVect );
}

void TowerBase::update()
{
    // TODO: timer
    // if
    build();
    destroy();

    // make sure is setting on the bottom
    m_pos->translation =
            m_dirVect * m_world->resolveHeightMapCache( m_heightCacheId );
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TowerBase::build()
{
    m_nextBlockTimer += NEXT_BLOCK_EASY_SPEED * omi::fpsManager.getTimeScale();
    if ( m_nextBlockTimer >= 1.0f )
    {
        int r = rand() % BUILD_EASY_PROB;
        if ( r == 0 )
        {
            m_nextBlockTimer = 0.0f;
            // get colour
            r = rand() % 2;
            tower::Colour colour = tower::RED;
            if ( r == 1 )
            {
                colour = tower::BLUE;
            }
            // get strength
            // TODO: difficulty
            r = rand() % 100;
            unsigned normProb = STR_EASY_NORM;
            unsigned hardProb = STR_EASY_STNG;
            tower::Strength st = tower::WEAK;
            if ( r >= normProb && r < hardProb )
            {
                st = tower::NORMAL;
            }
            else if ( r >= hardProb )
            {
                st = tower::STRONG;
            }
            // add a block
            Tower* t_t = new Tower(
                    m_stackRot, colour, st, BLOCK_HEIGHT * m_blocks.size() );
            m_blocks.push_back( t_t );
            addEntity( t_t );
        }
    }
}

void TowerBase::destroy()
{

}
