#include "Input.hpp"

namespace omi {

namespace input {

namespace {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

static int mouseScroll = 0;

} // namespace anonymous

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

glm::vec2 getMousePos()
{
    sf::Vector2i pos = sf::Mouse::getPosition();
    return glm::vec2(
        static_cast<float>( pos.x ),
        static_cast<float>( pos.y )
    );
}

bool mousePressed( mouse_button::Type button )
{
    if ( !omi_hasFocus )
    {
        return false;
    }

    return sf::Mouse::isButtonPressed( sf::Mouse::Button( button ) );
}

void setMouseScroll( int scroll )
{
    mouseScroll = scroll;
}

int getMouseScroll()
{
    return mouseScroll;
}

} // namespace input

} // namespace omi
