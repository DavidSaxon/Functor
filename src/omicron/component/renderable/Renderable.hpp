#ifndef OMICRON_COMPONENT_RENDERABLE_RENDERABLE_H_
#   define OMICRON_COMPONENT_RENDERABLE_RENDERABLE_H_

#include <algorithm>
#include <GL/glew.h>
#include <SFML/OpenGL.hpp>

#include "lib/Utilitron/MathUtil.hpp"

#include "src/omicron/Omicron.hpp"
#include "src/omicron/component/Component.hpp"
#include "src/omicron/component/Camera.hpp"
#include "src/omicron/component/Transform.hpp"
#include "src/omicron/rendering/lighting/LightData.hpp"
#include "src/omicron/rendering/shading/Material.hpp"
#include "src/omicron/resource/loader/Loaders.hpp"

namespace omi {

/******************************************************************************\
| Abstract class that defines any component that can be rendered via Omicron's |
| renderer.                                                                    |
\******************************************************************************/
class Renderable : public Component {
public:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // shadow shaders for renderables
    static Shader shadowShader;
    // glow shaders for the renderables
    static Shader glowShader;
    // the selection shader for renderables
    static Shader selectionShader;

    //! is true if this component will be rendered
    bool visible;
    //! is true if this component will cast a shadow
    bool castShadow;
    // is true if this should be rendered as an overlay element
    bool overlay;
    //! is true if this should be rendered as a GUI element
    bool gui;
    //! is true if the this renderable should render for selecting
    bool selectable;
    //! is true if the renderable is currently selected
    bool selected;

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Super constructor
    @param id the identifier of the component
    @param layer the render layer of the component
    @oaram transform the pointer to the transform to use for positioning
    @param material the material to use for the renderable*/
    Renderable(
            const std::string& id,
                  int          layer,
                  Transform*   transform,
            const Material     material );

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    virtual ~Renderable()
    {
    }

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Updates the renderable, is only called once per cycle, unlike render
    calls */
    virtual void update();

    /** #Hidden
    Render this component
    @param camera the camera used to render this
    @param shadowCamera the camera used for rendering shadows
    @param pointLights the list of point lights to use to render this */
    virtual void render(
            Camera* camera,
            Camera* shadowCamera,
            const LightData& lightData );

    /** Render this component for the shadow pass */
    virtual void renderShadow( Camera* camera );

    /** #Hidden
    Render this component for the glow pass */
    virtual void renderGlow( Camera* camera );

    /** #Hidden
    Render this component for colour picking */
    virtual void renderSelectable(
            Camera* camera,
            unsigned char red,
            unsigned char green,
            unsigned char blue );

    /** #Hidden
    Render this component for visibility checking */
    virtual void renderVisCheck(
            Camera* camera,
            unsigned char red,
            unsigned char green,
            unsigned char blue );

    /** Tells the renderable to ignore the given light */
    void ignoreLight( const std::string& lightId );

    //---------------------------------GETTERS----------------------------------

    /** #Override */
    virtual component::Type getType() const;

    /** @return the layer of the renderable */
    int getLayer() const;

    /** @return the transform used for positioning this renderable */
    Transform* getTransform();

    /** @return the material used for this renderable */
    Material& getMaterial();

    /** @return if this renderable should be visibility checked */
    bool getDoVisCheck() const;

    /** @return if this renderable should only do vis check */
    bool getOnlyVisCheck() const;

    /** @return if this renderable is visible by the camera */
    bool getVisCam() const;

    //---------------------------------SETTERS----------------------------------

    /** @param layer the new render layer of renderable */
    void setLayer( int layer );

    /** @param transform the new transform of the renderable */
    void setTransform( Transform* transform );

    /** Sets whether this renderable should perform visibility checking */
    void setDoVisCheck( bool state );

    /** Sets whether this renderable should only show in the visibility checking
    stage */
    void setOnlyVisCheck( bool state );

    /** #Hidden
    Sets whether this renderable is visible by the camera or not */
    void setVisCam( bool vis );

protected:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the render layer
    int m_layer;
    // the transform
    Transform* m_transform;
    // the material
    Material m_material;

    // the model matrix
    glm::mat4 m_modelMatrix;
    // the view matrix
    glm::mat4 m_viewMatrix;
    // the combined model, and view matrix
    glm::mat4 m_modelViewMatrix;
    // the transpose inverse of the modelView matrix
    glm::mat3 m_normalMatrix;
    // the combined model, view, and projection matrix
    glm::mat4 m_modelViewProjectionMatrix;

    std::vector<std::string> m_ignoreLights;

    // is true if this renderable will perform visibility checking
    bool m_doVisCheck;
    // is true if this renderable will not show in rendering stages but will
    // still be considered in visibility checking
    bool m_onlyVisCheck;

    // is true if the renderable is visible by the current camera
    bool m_visCam;

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Applies transformations
    @param the camera to get the view and projection matrices from */
    void applyTransformations();

    /** Calculates matrices */
    void calculateMatrices( Camera* camera );

    /** Sets up the shader for rendering and passes in all data */
    virtual void setShader(
            const LightData& lightData,
            Camera* camera,
            Camera* shadowCamera );

    /** Cleans up the shader */
    virtual void unsetShader();

    /** Defines the geometry of the renderable */
    virtual void draw() = 0;
};

} // namespace omi

#endif
