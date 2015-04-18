#include "ShadowMap.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

ShadowMap::ShadowMap( float resScale ) :
    m_frameBuffer ( 0 ),
    m_texture     ( 0 ),
    m_resScale    ( 4.0f )
{
    // initialise
    init();
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void ShadowMap::bind()
{
    // if the resolution has changed rebuild the render texture
    if ( m_resolution != renderSettings.getResolution() ||
         renderSettings.getShadowMapResolutionScale() != m_resScale )
    {
        init();
    }

    glBindFramebuffer( GL_FRAMEBUFFER, m_frameBuffer );
    // clear the render buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // set the view port to the size of the render texture
    glViewport(
        0,
        0,
        static_cast<GLsizei>( renderSettings.getResolution().x * m_resScale ),
        static_cast<GLsizei>( renderSettings.getResolution().y * m_resScale )
    );
}

void ShadowMap::unbind()
{
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );
    // revert the view port to screen size
    glViewport(
        0,
        0,
        static_cast<GLsizei>( displaySettings.getSize().x ),
        static_cast<GLsizei>( displaySettings.getSize().y )
    );
}

void ShadowMap::reload()
{
    init();
}

GLuint ShadowMap::getTexture() const
{
    return m_texture;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void ShadowMap::init()
{
    // store the resolution
    m_resolution = renderSettings.getResolution();
    m_resScale   = renderSettings.getShadowMapResolutionScale();

    // generate the frame buffer
    glGenFramebuffers( 1, &m_frameBuffer );
    glBindFramebuffer( GL_FRAMEBUFFER, m_frameBuffer );

    // generate the texture we will render depth to
    glGenTextures( 1, &m_texture );
    glBindTexture( GL_TEXTURE_2D, m_texture );
    // create an empty texture set up for depth
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT32,
        static_cast<GLsizei>( renderSettings.getResolution().x * m_resScale ),
        static_cast<GLsizei>( renderSettings.getResolution().y * m_resScale ),
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        0
    );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    // set up the frame buffer to render to our texture
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        m_texture,
        0
    );

    glDrawBuffer( GL_NONE );
    glReadBuffer( GL_NONE );

    // unbind
    glBindFramebuffer ( GL_FRAMEBUFFER,  0 );
    glBindTexture     ( GL_TEXTURE_2D,   0 );
}

} // namespace omi
