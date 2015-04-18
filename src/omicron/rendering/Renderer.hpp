#ifndef OMICRON_RENDERING_RENDERER_H_
#   define OMICRON_RENDERING_RENDERER_H_

#include <GL/glew.h>
#include <IL/il.h>
#include <memory>
#include <SFML/OpenGL.hpp>

#include "lib/Utilitron/MacroUtil.hpp"

class RenderSettings;

#include "src/omicron/Omicron.hpp"
#include "src/omicron/rendering/RenderLists.hpp"

namespace omi {

/****************************************************************************\
| The hub class controlling all rendering in Omicron. Rendering is performed |
| using OpenGL.                                                              |
\****************************************************************************/
class Renderer {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN(Renderer);

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new renderer */
    Renderer();

    //--------------------------------------------------------------------------
    //                                 DESTRUCTOR
    //--------------------------------------------------------------------------

    ~Renderer();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Performs one frame of rendering */
    void render();

    /** Clears all the components from the renderer */
    void clear();

    /** Sets the camera to use for rendering
    @param camera the new camera to use */
    void setCamera(Camera* camera);

    /** Removes the given camera if it is being used
    @param camera the camera to remove */
    void removeCamera(Camera* camera);

    /** Adds a renderable component to the render lists to be rendered
    @param renderable the renderable to add */
    void addRenderable(Renderable* renderable);

    /** Removes a renderable component from the render lists
    @param renderable the renderable to remove */
    void removeRenderable(Renderable* renderable);

    /** Adds a light to render lists
    @param light the light to add */
    void addLight( Light* light );

    /** Removes a light from the render lists
    @param light  the light remove */
    void removeLight( Light* light );

    /** Applies the OpenGL state */
    void applyGLState();

    /** Reloads the render textures begin used */
    void reloadRenderTextures();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the render lists containing all things to be rendered
    std::unique_ptr<RenderLists> m_renderLists;

    // the camera the used for perspective
    Camera* m_camera;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Applies settings */
    void applySettings();

    /** Initialises the renderer */
    void init();
};

} // namespace omi

#endif
