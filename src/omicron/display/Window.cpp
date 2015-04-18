#include "Window.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Window::Window() :
    m_cursorVisble( true ),
    m_renderer    ( NULL )
{
    // set up flags
    unsigned flags = sf::Style::Default;
    if ( displaySettings.getFullscreen() )
    {
        // flags = sf::Style::None;
        flags = sf::Style::Fullscreen;
    }

    // set up for openGL
    m_contextSettings.depthBits          = 24;
    m_contextSettings.stencilBits        = 8;
    m_contextSettings.antialiasingLevel  = 4;
    m_contextSettings.majorVersion       = 1;
    m_contextSettings.minorVersion       = 1;

    // non-full screen mode
    if ( !displaySettings.getFullscreen() )
    {
        // create the window using sfml
        m_window = std::unique_ptr<sf::Window>( new sf::Window(
            sf::VideoMode(
                static_cast<unsigned>( displaySettings.getSize().x ),
                static_cast<unsigned>( displaySettings.getSize().y ) ),
            displaySettings.getTitle(), flags, m_contextSettings )
        );
        // set the position of the window
        m_window->setPosition( sf::Vector2i(
            static_cast<int>( displaySettings.getPos().x ),
            static_cast<int>( displaySettings.getPos().y ) ) );
    }
    // full screen mode
    else
    {
        // create the window using sfml
        m_window = std::unique_ptr<sf::Window>( new sf::Window(
            sf::VideoMode::getDesktopMode(),
            displaySettings.getTitle(), flags, m_contextSettings )
        );
        // update the display settings with the new resolution and position
        displaySettings.setSize( glm::vec2(
            m_window->getSize().x, m_window->getSize().y ) );
        displaySettings.setPos( glm::vec2( 0 ) );
    }

    // set v sync
    m_window->setVerticalSyncEnabled( displaySettings.getVsync() );
    // set cursor visibility
    m_window->setMouseCursorVisible( m_cursorVisble );
    // set frame-rate cap
    m_window->setFramerateLimit( displaySettings.getFrameRateCap() );
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Window::update()
{
    m_window->setVisible(true);

    // check if there has been a change in settings
    if ( displaySettings.check() )
    {
        // check if the windowing mode has changed
        if ( displaySettings.checkMode() )
        {
            // windowed mode
            if ( !displaySettings.getFullscreen() )
            {
                // create a new window
                unsigned flags = sf::Style::Default;
                m_window->create(
                    sf::VideoMode(
                        static_cast<unsigned>( displaySettings.getSize().x ),
                        static_cast<unsigned>( displaySettings.getSize().y )
                    ),
                    displaySettings.getTitle(),
                    flags,
                    m_contextSettings
                );
            }
            // fullscreen mode
            else
            {
                // create a new window
                unsigned flags = sf::Style::Fullscreen;
                m_window->create(
                    sf::VideoMode::getDesktopMode(),
                    displaySettings.getTitle(),
                    flags,
                    m_contextSettings
                );

                // update the display settings with the new resolution and
                // position
                displaySettings.setSize( glm::vec2(
                     m_window->getSize().x,
                     m_window->getSize().y
                ) );
                displaySettings.setPos( glm::vec2( 0 ) );
            }

            // reapply the GL context
            glewInit();
            m_renderer->applyGLState();
            m_renderer->reloadRenderTextures();
        }

        if ( !displaySettings.getFullscreen() )
        {
            // set the size of the window
            m_window->setSize( sf::Vector2u(
                    static_cast<unsigned>( displaySettings.getSize().x ),
                    static_cast<unsigned>( displaySettings.getSize().y )
            ) );
            // set the position of the window
            m_window->setPosition( sf::Vector2i(
                static_cast<int>( displaySettings.getPos().x ),
                static_cast<int>( displaySettings.getPos().y )
            ) );
        }
        //  set title
        m_window->setTitle( displaySettings.getTitle() );
        // set vertical sync
        m_window->setVerticalSyncEnabled( displaySettings.getVsync() );
        // set frame-rate cap
        m_window->setFramerateLimit( displaySettings.getFrameRateCap() );
    }
    // set cursor visibility
    if ( omi_hasFocus )
    {
        m_window->setMouseCursorVisible( m_cursorVisble );
    }
    else
    {
        m_window->setMouseCursorVisible( true );
    }

    // check events
    sf::Event event;
    // is true if we get a mouse wheel event
    bool mouseWheel = false;
    while ( m_window->pollEvent( event ) )
    {
        // TODO: this should be override able
        // close button is pressed
        if ( event.type == sf::Event::Closed )
        {
            exit( 0 );
        }
        // mouse scrolling
        if ( event.type == sf::Event::MouseWheelMoved )
        {
            mouseWheel = true;
            input::setMouseScroll( event.mouseWheel.delta );
        }
        // focus lost
        if ( event.type == sf::Event::LostFocus )
        {
            omi_hasFocus = false;
        }
        if ( event.type == sf::Event::GainedFocus )
        {
            omi_hasFocus = true;
        }
    }
    // there has been no mouse scrolling
    if ( !mouseWheel )
    {
        input::setMouseScroll( 0 );
    }

    // redisplay the window
    m_window->display();
}

void Window::setRenderer( Renderer* renderer )
{
    m_renderer = renderer;
}

void Window::setCursorVisble( bool visible )
{
    m_cursorVisble = visible;
}

} // namespace omi
