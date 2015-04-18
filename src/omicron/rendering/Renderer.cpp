#include "Renderer.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Renderer::Renderer() :
    m_camera(NULL)
{
    // initialise
    init();
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

Renderer::~Renderer()
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Renderer::render() {

    // update any settings that have changed
    applySettings();

    // clear the window
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // load the identity matrix
    glLoadIdentity();

    // render the render lists
    m_renderLists->render(m_camera);

    // swap the buffers
    // TODO:?
}

void Renderer::clear() {

    m_camera = NULL;
    m_renderLists->clear();
}

void Renderer::setCamera(Camera* camera) {

    m_camera = camera;
    camScale = m_camera->getTransform()->scale;
}

void Renderer::removeCamera(Camera* camera) {

    if (m_camera == camera) {

        m_camera = NULL;
    }
}

void Renderer::addRenderable(Renderable* renderable) {

    m_renderLists->addRenderable(renderable);
}

void Renderer::removeRenderable(Renderable* renderable) {

    m_renderLists->removeRenderable(renderable);
}

void Renderer::addLight( Light* light )
{
    m_renderLists->addLight( light );
}

void Renderer::removeLight( Light* light )
{
    m_renderLists->removeLight( light );
}

void Renderer::applyGLState()
{
    // apply the render settings
    applySettings();

    // apply non changeable settings
    glEnable( GL_BLEND );
    glBlendEquation( GL_FUNC_ADD );
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glCullFace( GL_BACK );
    glClearDepth( 1.0f );
    glEnable( GL_TEXTURE_2D );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    glEnable( GL_MULTISAMPLE );
}

void Renderer::reloadRenderTextures()
{
    m_renderLists->reloadRenderTextures();
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Renderer::applySettings() {

    if (renderSettings.check()) {

        // depth test
        renderSettings.getDepthTest() ?
            glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
        // back face culling
        renderSettings.getBackFaceCulling() ?
            glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);

        glClearColor(
            renderSettings.getClearColour().r,
            renderSettings.getClearColour().g,
            renderSettings.getClearColour().b,
            renderSettings.getClearColour().a
        );
    }
}

void Renderer::init() {

    // apply the OpenGL state
    applyGLState();

    // initialise DevIL
    ilInit();

    // create the render lists
    m_renderLists = std::unique_ptr<RenderLists>(new RenderLists());

    // load the shadpw shader for renderables
    Renderable::shadowShader = loader::loadShaderFromFiles(
        "res/gfx/shader/omicron/shadow_vertex.glsl",
        "res/gfx/shader/omicron/shadow_fragment.glsl"
    );
    // load the glow shader for renderables
    Renderable::glowShader = loader::loadShaderFromFiles(
        "res/gfx/shader/omicron/glow_vertex.glsl",
        "res/gfx/shader/omicron/glow_fragment.glsl"
    );
    // load the selection shader for renderables
    Renderable::selectionShader = loader::loadShaderFromFiles(
        "res/gfx/shader/omicron/selection_vertex.glsl",
        "res/gfx/shader/omicron/selection_fragment.glsl"
    );
}

} // namespace omi
