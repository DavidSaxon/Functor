#include "Input.hpp"

namespace omi {

namespace input {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

bool isKeyPressed( key::Type key )
{
    if ( !omi_hasFocus )
    {
        return false;
    }

    return sf::Keyboard::isKeyPressed( sf::Keyboard::Key( key ) );
}

} // namespace input

} // namespace omi
