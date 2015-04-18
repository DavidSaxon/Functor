#ifndef OMICRON_ENTITY_RENDERING_RENDERLISTS_H_
#   define OMICRON_ENTITY_RENDERING_RENDERLISTS_H_

#include <algorithm>
#include <map>
#include <memory>
#include <sstream>
#include <vector>
#include <boost/thread.hpp>

#include "lib/Utilitron/MacroUtil.hpp"

#include "src/omicron/component/light/DirectionalLight.hpp"
#include "src/omicron/component/light/PointLight.hpp"
#include "src/omicron/component/light/SpotLight.hpp"
#include "src/omicron/component/renderable/Renderable.hpp"
#include "src/omicron/input/Input.hpp"
#include "src/omicron/rendering/VisibilityCheckThread.hpp"
#include "src/omicron/rendering/lighting/ShadowMap.hpp"
#include "src/omicron/rendering/render_texture/BlurHorRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/BlurVertRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/FinalRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/GlowBlurHorRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/GlowBlurVertRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/GlowCollateRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/GlowFirstPassRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/GuiRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/StdRenderTexture.hpp"
#include "src/omicron/rendering/render_texture/VisCheckRenderTexture.hpp"


namespace omi {

//-----------------------------------TYPEDEF------------------------------------

typedef std::map<int, std::vector<Renderable*>> t_RenderableMap;

/**********************************\
| Object for transparency sorting. |
\**********************************/
struct RenderableDepthSorter {

    // the camera to sort depth with
    Camera* camera;

    /** The sorting function */
    bool operator ()( Renderable* a, Renderable* b )
    {

        // compared based on their distances from the camera
        float distanceA = glm::distance(
            a->getTransform()->translation,
            camera->getTransform()->translation
        );

        float distanceB = glm::distance(
            b->getTransform()->translation,
            camera->getTransform()->translation
        );

        return distanceA < distanceB;
    }
};

/*************************************************************************\
| A set of lists that contain all objects to be rendered by the renderer. |
\*************************************************************************/
class RenderLists {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN( RenderLists );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new set of render lists */
    RenderLists();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~RenderLists();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Renders all of the renderable components contained within the render
    lists
    @param the camera to use for rendering */
    void render( Camera* camera );

    /** Reloads the render textures being used */
    void reloadRenderTextures();

    /** Removes all components from the render lists */
    void clear();

    /** Adds a renderable component to the render lists
    @param renderable the renderable to add */
    void addRenderable( Renderable* renderable );

    /** Removes a renderable from the render lists
    @param renderable the renderable to remove */
    void removeRenderable( Renderable* renderable );

    /** Adds a light to render lists
    @param light the light to add */
    void addLight( Light* light );

    /** Removes a light from the render lists
    @param light  the light remove */
    void removeLight( Light* light );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the list of renderables
    std::vector<Renderable*> m_renderables;
    // the list of lights
    std::vector<Light*> m_lights;

    // shadow map
    ShadowMap m_shadowMap;

    // visibility checking render texture
    VisCheckRenderTexture m_visCheckRenTex;
    // glow render textures
    GlowFirstPassRenderTexture m_glowFirstPassRenTex;
    GlowBlurHorRenderTexture m_glowBlurHorRenTex;
    GlowBlurVertRenderTexture m_glowBlurVertRenTex;
    GlowCollateRenderTexture m_glowCollateRenTex;
    // the standard render texture
    StdRenderTexture m_stdRenderTexture;
    // the overlay render texture
    StdRenderTexture m_overlayRenderTexture;
    // the blur textures
    BlurHorRenderTexture m_blurHorTexture;
    BlurVertRenderTexture m_blurVertTexture;
    // the gui render texture
    GuiRenderTexture m_guiRenderTexture;
    // the final render texture for post effects
    FinalRenderTexture m_finalRenTex;

    // the depth sorter
    RenderableDepthSorter depthSorter;

    // the thread for visibility checking
    std::unique_ptr<boost::thread> m_visCheckThread;
    // the pixel buffer for visibility checking
    std::vector<GLubyte> m_visCheckBuffer;
    // the visibility checking colour map
    std::map<unsigned, Renderable*> m_visColourMap;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Renders if a selectable element */
    void renderSelectable(
            Renderable* renderable,
            Camera* camera,
            std::map<unsigned, Renderable*>& colourMap,
            unsigned char& red,
            unsigned char& green,
            unsigned char& blue );


    /** Renders an element for visibility checking */
    void renderVisibilty(
            Renderable* renderable,
            Camera* camera,
            std::map<unsigned, Renderable*>& colourMap,
            unsigned char& red,
            unsigned char& green,
            unsigned char& blue );

    /** Builds light data */
    void buildLightData(
            Camera* camera,
            Light* shadowCaster,
            LightData& lightData );

};

} // namespace omi

#endif
