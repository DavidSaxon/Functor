#ifndef OMICRON_COMPONENT_CAMERA_H_
#   define OMICRON_COMPONENT_CAMERA_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <GL/glew.h>
#include <iostream>
#include <SFML/OpenGL.hpp>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtx/transform.hpp"

#include "lib/Utilitron/MathUtil.hpp"


#include "src/omicron/Omicron.hpp"
#include "src/omicron/component/Component.hpp"
#include "src/omicron/component/Transform.hpp"

namespace omi {

namespace cam {

// the mode of the camera
enum Mode {

    PERSPECTIVE,
    ORTHOGRAPHIC,
    SHADOW
};

} // namespace cam

/***********************************************************************\
| A camera used to render perspective from. Note that the most recently |
| created camera will be the one that is used for rendering.            |
\***********************************************************************/
class Camera : public Component {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTORS
    //--------------------------------------------------------------------------

    /** Creates a new camera, and uses default fov, near clip, and far clip
    @param id the identifier of the component
    @param mode the mode of the camera
    @param transform a pointer to the transform to use for the camera */
    Camera( const std::string& id,
                 cam::Mode    mode,
                 Transform*   transform );

    /** Creates a new camera and uses default near and far clipping planes
    @param id the identifier of the component
    @param mode the mode of the camera
    @param transform a pointer to the transform to use for the camera
    @param fov the field of view of the camera */
    Camera( const std::string& id,
                 cam::Mode    mode,
                 Transform*   transform,
                 float        fov );

     /** Creates a new camera, and uses default fov
     @param id the identifier of the component
     @param mode the mode of the camera
     @param transform a pointer to the transform to use for the camera
     @param nearClip the near clipping plane
     @param farClip the far clipping plane */
     Camera( const std::string& id,
                  cam::Mode    mode,
                  Transform*   transform,
                  float        nearClip,
                  float        farClip );

     /** Creates a new camera
     @param id the identifier of the component
     @param mode the mode of the camera
     @param transform a pointer to the transform to use for the camera
     @param fov the field of view of the camera
     @param nearClip the near clipping plane
     @param farClip the far clipping plane */
     Camera( const std::string& id,
                  cam::Mode    mode,
                  Transform*   transform,
                  float        fov,
                  float        nearClip,
                  float        farClip );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    component::Type getType() const;

    /** #Hidden
    Applies the effects of the camera to the render matrices */
    void apply();

    //---------------------------------GETTERS----------------------------------

    /** @return the mode of the camera */
    cam::Mode getMode() const;

    /** @return the transform used by the camera */
    Transform* getTransform();

    /** @return the computed projection matrix for this camera */
    const glm::mat4& getProjectionMatrix();

    /** @return the computed view matrix for this camera */
    const glm::mat4& getViewMatrix();

    /** @return the field of view of the camera */
    float getFOV() const;

    /** @return the near clipping plane of the camera */
    float getNearClippingPlane() const;

    /** @return the far clipping plane of the camera */
    float getFarClippingPlane() const;

    /** @return the transform used for offsetting the camera in shadow mode */
    const Transform* getShadowOffset() const;

    /** @return the exposure of the camera */
    float getExposure() const;

    //---------------------------------SETTERS----------------------------------

    /** @param the new mode of the camera */
    void setMode( cam::Mode mode );

    /** @param the new transform to be used by the camera */
    void setTransform( Transform* transform );

    /** @param fov the new field of view of the camera */
    void setFOV( float fov );

    /** @param nearClip the new near clipping plane of the camera */
    void setNearClip( float nearClip );

    /** @param farClip the new far clipping plane of the camera */
    void setFarClip( float farClip );

    /** @param shadowOffset the transform used for offsetting the camera in
    shadow mode */
    void setShadowOffset( Transform* shadowOffset );

    /** Sets the exposure value of this camera */
    void setExposure( float exposure );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the mode of the camera
    cam::Mode m_mode;
    // the transform of the camera
    Transform* m_transform;
    // the transform used for offsetting in shadow mode
    Transform* m_shadowOffset;

    // the projection matrix
    glm::mat4 m_projectionMatrix;
    // the view matrix
    glm::mat4 m_viewMatrix;

    // the field of view of the camera
    float m_fov;

    // the near clipping plane
    float m_nearClip;
    // the far clipping plane
    float m_farClip;

    // the exposure of the camera (i.e. how much light it lets in)
    float m_exposure;
};

 } // namespace omi

#endif
