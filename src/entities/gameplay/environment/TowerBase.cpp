#include "TowerBase.hpp"

#include "src/data/Globals.hpp"
#include "src/entities/gameplay/environment/Tower.hpp"
#include "src/entities/gameplay/environment/World.hpp"

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace
{
static const float BLOCK_HEIGHT = 0.06f;
static const float NEXT_BLOCK_EASY_SPEED = 0.005f;
static const float NEXT_BLOCK_MEDIUM_SPEED = 0.01f;
static const float NEXT_BLOCK_HARD_SPEED = 0.015f;
static const float BUILD_EASY_PROB       = 1.65f;
static const float BUILD_MEDIUM_PROB     = 2.0f;
static const float BUILD_HARD_PROB       = 1.0f;
static const int STR_EASY_NORM         = 60;
static const int STR_EASY_STNG         = 85;
static const int STR_MEDI_NORM         = 50;
static const int STR_MEDI_STNG         = 75;
static const int STR_HARD_NORM         = 70;
static const int STR_HARD_STNG         = 30;
} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TowerBase::TowerBase( World* world, const glm::vec3& rotation, float timeout )
    :
    m_world             ( world ),
    m_rotation          ( rotation ),
    m_startTimer        ( 0.0f ),
    m_timeOut           ( timeout ),
    m_nextBlockTimer    ( 0.0f ),
    m_baseHeight        ( 0.015f ),
    m_height            ( 0.0f ),
    m_started           ( false ),
    m_nextBlockRandTimer( 0.0f )
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

    // add mesh
    m_mesh =
            omi::ResourceManager::getMesh( "tower_base", "", m_stackRot );
    m_mesh->getMaterial().specular =
            new omi::Specular( 64.0f, glm::vec3( 0.5f, 0.5f, 0.5f ) );
    m_components.add( m_mesh );

    // register in cache
    m_heightCacheId = m_world->addHeightMapCache( m_dirVect );
}

void TowerBase::update()
{
    // skip if omicron is paused
    if ( global::pause )
    {
        return;
    }

    // make sure is setting on the bottom
    m_pos->translation =
            m_dirVect *
            ( m_world->resolveHeightMapCache( m_heightCacheId ) +
              m_baseHeight );
    // set height of blocks
    std::vector<Tower*>::iterator it = m_blocks.begin();
    for ( ; it != m_blocks.end(); ++it )
    {
        ( *it )->setAddHeight(
                util::math::clamp<float>( m_height, 0.0f, BLOCK_HEIGHT ) );
    }

    // glow bottom
    if ( !m_blocks.empty() )
    {
        m_blocks[ 0 ]->glowMyShitUp();
    }

    if ( !m_started )
    {
        return;
    }

    if ( m_startTimer > m_timeOut )
    {
        build();
        destroy();
    }
    else
    {
        m_startTimer += 0.01f * omi::fpsManager.getTimeScale();
    }

    // shift add height down
    if ( m_height > 0.0f )
    {
        m_height -= 0.005f * omi::fpsManager.getTimeScale();
    }
    else
    {
        m_height = 0.0f;
    }
}

void TowerBase::start()
{
    m_started = true;
    m_nextBlockTimer = 0.0f;
    m_startTimer     = 0.0f;
    m_nextBlockRandTimer = static_cast<float>( rand() % 1000 ) / 1000.0f;
    m_nextBlockRandTimer *= BUILD_EASY_PROB;
}

void TowerBase::stop()
{
    m_started = false;
    std::vector<Tower*>::iterator it = m_blocks.begin();
    for ( ; it != m_blocks.end(); ++it )
    {
        ( *it )->destroy();
    }
    m_blocks.clear();
}

unsigned TowerBase::getShit()
{
    return m_blocks.size();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TowerBase::build()
{
    m_nextBlockTimer += NEXT_BLOCK_EASY_SPEED * omi::fpsManager.getTimeScale();
    if ( m_nextBlockTimer >= 1.0f + m_nextBlockRandTimer )
    {

        int r = 0;
        if ( r == 0 )
        {
            m_nextBlockTimer = 0.0f;
            m_nextBlockRandTimer = static_cast<float>( rand() % 1000 ) / 1000.0f;
            m_nextBlockRandTimer *= BUILD_EASY_PROB;
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
            int normProb = STR_EASY_NORM;
            int hardProb = STR_EASY_STNG;
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

            // update the base level
            if ( m_blocks.size() == 1 )
            {
                m_currentLevel =
                        m_world->resolveHeightMapCache( m_heightCacheId );
            }
        }
    }
}

void TowerBase::destroy()
{
    if ( !m_blocks.empty() )
    {
        Tower* tw = m_blocks[ 0 ];
        float fuck = m_world->resolveHeightMapCache( m_heightCacheId );
        bool des = false;

        if ( tw->getColour() == tower::BLUE )
        {
            if ( fuck > m_currentLevel  )
            {
                m_currentLevel = fuck;
            }
            else if ( m_currentLevel - fuck >= tw->getChangeDis() ||
                      m_currentLevel <= 0.05f )
            {
                tw->destroy();
                des = true;
                m_currentLevel = fuck;
            }
        }
        else
        {
            if ( fuck < m_currentLevel  )
            {
                m_currentLevel = fuck;
            }
            else if ( fuck - m_currentLevel >= tw->getChangeDis() )
            {
                tw->destroy();
                des = true;
                m_currentLevel = fuck;
            }
        }

        // move the rest of the tower down
        if ( des )
        {
            // remove from the vector
            m_blocks.erase( m_blocks.begin() );
            m_height = BLOCK_HEIGHT * 3.0f;

            // shift other blocks down
            for ( unsigned i = 0; i < m_blocks.size(); ++i )
            {
                m_blocks[ i ]->setHeight( i * BLOCK_HEIGHT );
            }
        }
    }
}
