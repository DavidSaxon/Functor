#include "Camera.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                   CONSTANTS
//------------------------------------------------------------------------------

namespace {

static const float SHADOW_RANGE    = 250.0f;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Camera::Camera( const std::string& id,
                     cam::Mode    mode,
                     Transform*   transform )
    :
    Component     ( id ),
    m_mode        ( mode ),
    m_transform   ( transform ),
    m_shadowOffset( NULL ),
    m_fov         ( 60.0f ),
    m_nearClip    ( 0.001f ),
    m_farClip     ( 1000.0f ),
    m_exposure    ( 1.0f )
{
}

Camera::Camera( const std::string& id,
                      cam::Mode    mode,
                      Transform*   transform,
                      float        fov )
    :
    Component     ( id ),
    m_mode        ( mode ),
    m_transform   ( transform ),
    m_shadowOffset( NULL ),
    m_fov         ( fov ),
    m_nearClip    ( 0.001f ),
    m_farClip     ( 1000.0f ),
    m_exposure    ( 1.0f )
{
}

Camera::Camera( const std::string& id,
                      cam::Mode    mode,
                      Transform*   transform,
                      float        nearClip,
                      float        farClip )
    :
    Component     ( id ),
    m_mode        ( mode ),
    m_transform   ( transform ),
    m_shadowOffset( NULL ),
    m_fov         ( 60.0f ),
    m_nearClip    ( nearClip ),
    m_farClip     ( farClip ),
    m_exposure    ( 1.0f )
{
}

Camera::Camera( const std::string& id,
                      cam::Mode    mode,
                      Transform*   transform,
                      float        fov,
                      float        nearClip,
                      float        farClip )
    :
    Component     ( id ),
    m_mode        ( mode ),
    m_transform   ( transform ),
    m_shadowOffset( NULL ),
    m_fov         ( fov ),
    m_nearClip    ( nearClip ),
    m_farClip     ( farClip ),
    m_exposure    ( 1.0f )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

component::Type Camera::getType() const
{
    return component::CAMERA;
}

void Camera::apply()
{
    // projection matrix
    float aspectRatio =
        renderSettings.getResolution().x / renderSettings.getResolution().y;
    // perspective camera
    if ( m_mode == cam::PERSPECTIVE )
    {
        m_projectionMatrix =
            glm::perspective(
                m_fov * util::math::DEGREES_TO_RADIANS,
                aspectRatio,
                m_nearClip,
                m_farClip
            );
    }
    // orthographic camera
    else if ( m_mode == cam::ORTHOGRAPHIC )
    {
        m_projectionMatrix = glm::ortho(
                -aspectRatio, aspectRatio, -1.0f, 1.0f, m_nearClip, m_farClip );
    }
    // shadow camera
    else
    {
        // set up projection matrix
        float camSize = renderSettings.getShadowFrustumSize();
        m_projectionMatrix = glm::ortho(
            -camSize,
             camSize,
            -camSize,
             camSize,
            -SHADOW_RANGE,
             SHADOW_RANGE );
        // set up view matrix
        m_viewMatrix = glm::lookAt(
            m_transform->translation,
            glm::vec3( 0, 0, 0 ),
            glm::vec3( 0, 1, 0 )
        );

        if ( m_shadowOffset == NULL )
        {
            return;
        }

        // apply shadow offset
        glm::vec3 translation( m_shadowOffset->computeTranslation() );
        m_viewMatrix *= glm::translate( -translation );

        // don't continue processing
        return;
    }

    // view matrix
    m_viewMatrix = glm::lookAt(
        glm::vec3( 0, 0, m_nearClip ),
        glm::vec3( 0, 0, 0 ),
        glm::vec3( 0, 1, 0 )
    );

    // don't transform if no tranform has been given
    if ( m_transform == NULL )
    {
        return;
    }

    m_transform->applyReverse( m_viewMatrix );
}

//-----------------------------------GETTERS------------------------------------

cam::Mode Camera::getMode() const
{
    return m_mode;
}

Transform* Camera::getTransform()
{
    return m_transform;
}

const glm::mat4& Camera::getProjectionMatrix()
{
    return m_projectionMatrix;
}

const glm::mat4& Camera::getViewMatrix()
{
    return m_viewMatrix;
}

float Camera::getFOV() const
{
    return m_fov;
}

float Camera::getNearClippingPlane() const
{
    return m_nearClip;
}

float Camera::getFarClippingPlane() const
{
    return m_farClip;
}

const Transform* Camera::getShadowOffset() const
{
    return m_shadowOffset;
}

float Camera::getExposure() const
{
    return m_exposure;
}

//-----------------------------------SETTERS------------------------------------

void Camera::setMode( cam::Mode mode )
{
    m_mode = mode;
}

void Camera::setTransform( Transform* transform )
{
    m_transform = transform;
}

void Camera::setFOV( float fov )
{
    m_fov = fov;
}

void Camera::setNearClip( float nearClip )
{
    m_nearClip = nearClip;
}

void Camera::setFarClip( float farClip )
{
    m_farClip = farClip;
}

void Camera::setShadowOffset( Transform* shadowOffset )
{
    m_shadowOffset = shadowOffset;
}

void Camera::setExposure( float exposure )
{
    m_exposure = exposure;
}

} // namespace omi
