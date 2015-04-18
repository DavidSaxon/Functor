#ifndef OMICRON_DISPLAY_WINDOW_H_
#   define OMICRON_DISPLAY_WINDOW_H_

#include <GL/glew.h>
#include <memory>
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>

#include "lib/Utilitron/MacroUtil.hpp"

class DisplaySettings;

#include "src/omicron/Omicron.hpp"
#include "src/omicron/input/Input.hpp"
#include "src/omicron/rendering/Renderer.hpp"

namespace omi {

/**************************************************************************\
| A display window which Omicron will render to. Currently only one active |
| window is supported.                                                     |
\**************************************************************************/
class Window {
private:

    //--------------------------------------------------------------------------
    //                                RESTRICTIONS
    //--------------------------------------------------------------------------

    DISALLOW_COPY_AND_ASSIGN( Window );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------
    /** Creates a new window
    #WARNING: currently only one active window is supported */
    Window();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Updates the window
    #NOTE: any changes to the window should be done through Omicron's display
    settings. This is a back end class that should only be used by Omicron */
    void update();

    /** @param passes in a pointer to the renderer */
    void setRenderer( Renderer* renderer );

    /** @param visible whether the cursor is visible or not */
    void setCursorVisble( bool visible );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the window object
    std::unique_ptr<sf::Window> m_window;
    // whether the cursor should be visible or not
    bool m_cursorVisble;
    // the window context settings
    sf::ContextSettings m_contextSettings;
    // a pointer to the renderer
    Renderer* m_renderer;
};

} // namespace omi

#endif
