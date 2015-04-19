#include "KeyFrameMesh.hpp"

#include "src/data/Globals.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

KeyFrameMesh::KeyFrameMesh(
        const std::string& id,
        int layer,
        Transform* transform,
        std::map<std::string, std::vector<Geometry*>> geometry,
        std::map<std::string, std::vector<unsigned>> frames,
        const std::string& defaultAni,
        Material material ) :
    Renderable  ( id, layer, transform, material ),
    m_geometry  ( geometry ),
    m_frameMap  ( frames ),
    m_defaultAni( defaultAni ),
    m_geo1      ( NULL ),
    m_geo2      ( NULL ),
    m_transGeo  ( NULL ),
    m_speed     ( 1.0f ),
    m_currAni   ( defaultAni ),
    m_nextAni   ( defaultAni ),
    m_transition( -1 ),
    m_frame     ( 0.0f ),
    m_key       ( 0 ),
    m_transFrame( 0.0f ),
    m_r1        ( 1.0f ),
    m_r2        ( 0.0f ),
    m_tr1       ( 1.0f ),
    m_tr2       ( 0.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void KeyFrameMesh::update()
{
    // super call
    Renderable::update();

    // don't animate if the engine is paused
    if ( global::pause )
    {
        return;
    }

    // perform a transition update
    if ( m_transition >= 0 )
    {
        transitionUpdate();
    }
    else
    {
        normalUpdate();
    }

    unsigned length = m_geometry[ m_currAni ].size();
    // get the geometries are interpolating between
    m_geo1 = m_geometry[ m_currAni ][ m_key ];
    m_geo2 = m_geometry[ m_currAni ][ ( m_key + 1 ) % length ];
    m_transGeo = m_geometry[ m_nextAni ][ 0 ];
}

void KeyFrameMesh::transition( const std::string animation, unsigned frames )
{
    m_nextAni = animation;
    m_transition = static_cast<int>( frames );
    m_transFrame = 0;
}

bool KeyFrameMesh::isTransitioning()
{
    return m_transition >= 0;
}

float KeyFrameMesh::getSpeed() const
{
    return m_speed;
}

void KeyFrameMesh::setSpeed( float speed )
{
    m_speed = speed;
}

float KeyFrameMesh::getFrame() const
{
    return ( m_key * 9.0f ) + m_frame;
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void KeyFrameMesh::draw()
{
    glBegin( GL_TRIANGLES );
    for ( unsigned i = 0; i < m_geo1->vertices.size(); ++i ) {

        if ( m_geo1->normals.size() > 0 )
        {
            // calculate interpolated normals
            float nX = ( m_geo1->normals[ i ].x * m_r1 ) +
                       ( m_geo2->normals[ i ].x * m_r2 );
            nX = ( nX * m_tr1 ) + ( m_transGeo->normals[i].x * m_tr2 );
            float nY = ( m_geo1->normals[ i ].y * m_r1 ) +
                       ( m_geo2->normals[ i ].y * m_r2 );
            nY = ( nY * m_tr1 ) + ( m_transGeo->normals[i].y * m_tr2 );
            float nZ = ( m_geo1->normals[ i ].z * m_r1 ) +
                       ( m_geo2->normals[ i ].z * m_r2 );
            nZ = ( nZ * m_tr1 ) + ( m_transGeo->normals[i].z * m_tr2 );
            // draw normals
            glNormal3f( nX, nY, nZ );
        }

        if ( m_geo1->uv.size() > 0 )
        {
            // calculate interpolated uvs
            float uvX = ( m_geo1->uv[ i ].x * m_r1 ) +
                        ( m_geo2->uv[ i ].x * m_r2 );
            uvX = ( uvX * m_tr1 ) + ( m_transGeo->uv[i].x * m_tr2 );
            float uvY = ( m_geo1->uv[ i ].y * m_r1 ) +
                        ( m_geo2->uv[ i ].y * m_r2 );
            uvY = ( uvY * m_tr1 ) + ( m_transGeo->uv[i].y * m_tr2 );
            // draw uv co-ords
            glTexCoord2f( uvX, uvY );
        }

        // calculate interpolated vertices
        float vX = ( m_geo1->vertices[ i ].x * m_r1 ) +
                   ( m_geo2->vertices[ i ].x * m_r2 );
        vX = ( vX * m_tr1 ) + ( m_transGeo->vertices[i].x * m_tr2 );
        float vY = ( m_geo1->vertices[ i ].y * m_r1 ) +
                   ( m_geo2->vertices[ i ].y * m_r2 );
        vY = ( vY * m_tr1 ) + ( m_transGeo->vertices[i].y * m_tr2 );
        float vZ = ( m_geo1->vertices[ i ].z * m_r1 ) +
                   ( m_geo2->vertices[ i ].z * m_r2 );
        vZ = ( vZ * m_tr1 ) + ( m_transGeo->vertices[i].z * m_tr2 );
        // draw vertices
        glVertex3f( vX, vY, vZ );
    }
    glEnd();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void KeyFrameMesh::normalUpdate()
{
    // get the current number if keys
    unsigned length = m_geometry[ m_currAni ].size();

    // get the current frame count
    float frameCount = static_cast<float>( m_frameMap[ m_currAni ][ m_key ] );

    // increase the frame
    m_frame += m_speed * omi::fpsManager.getTimeScale();
    if ( m_frame > frameCount )
    {
        m_frame -= frameCount;
        m_key = ( m_key + 1 ) % length;
    }

    // calculate ratios
    m_r2 = m_frame / static_cast<float>( m_frameMap[ m_currAni ][ m_key ] );
    m_r1 = 1.0f - m_r2;
}

void KeyFrameMesh::transitionUpdate()
{
    // get the current frame count
    float frameCount = static_cast<float>( m_transition );

    // increase the transition frame
    m_transFrame += m_speed * omi::fpsManager.getTimeScale();
    if ( m_transFrame > frameCount )
    {
        // clean up the transition
        m_transition = -1;
        m_currAni = m_nextAni;
        m_frame = m_transFrame - frameCount;
        m_key = 0;
        m_r2 = m_frame / static_cast<float>( m_frameMap[ m_currAni ][ m_key ] );
        m_r1 = 1.0f - m_r2;
        m_tr1 = 1.0f;
        m_tr2 = 0.0f;

        return;
    }

    // calculate ratios
    m_tr2 = m_transFrame / frameCount;
    m_tr1 = 1.0f - m_tr2;
}

} // namespace omi
