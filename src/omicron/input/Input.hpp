#ifndef OMICRON_INPUT_INPUT_H_
#   define OMICRON_INPUT_INPUT_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <SFML/Window.hpp>

#include "lib/glm/glm.hpp"

#include "src/omicron/Omicron.hpp"

namespace omi
{

/*********************************\
| functions handling input events |
\*********************************/
namespace input {

//------------------------------------------------------------------------------
//                                  ENUMERATORS
//------------------------------------------------------------------------------

namespace mouse_button {

enum Type {
    LEFT,
    RIGHT,
    MIDDLE
};

} // namespace mouse

namespace key {

enum Type {
    UNKNOWN = -1,
    A = 0,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    v,
    W,
    X,
    Y,
    Z,
    NUM_0,
    NUM_1,
    NUM_2,
    NUM_3,
    NUM_4,
    NUM_5,
    NUM_6,
    NUM_7,
    NUM_8,
    NUM_9,
    ESCAPE,
    LEFT_CONTROL,
    LEFT_SHIFT,
    LEFT_ALT,
    LEFT_SYSTEM,
    RIGHT_CONTROL,
    RIGHT_SHIFT,
    RIGHT_ALT,
    RIGHT_SYSTEM,
    MENU,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    SEMICOLON,
    COMMA,
    PERIOD,
    QUOTE,
    SLASH,
    BACKSLASH,
    TILDE,
    EQUAL,
    DASH,
    SPACE,
    RETURN,
    BACKSPACE,
    TAB,
    PAGE_UP,
    PAGE_DOWN,
    END,
    HOME,
    INSERT,
    DEL,
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NUMPAD_0,
    NUMPAD_1,
    NUMPAD_2,
    NUMPAD_3,
    NUMPAD_4,
    NUMPAD_5,
    NUMPAD_6,
    NUMPAD_7,
    NUMPAD_8,
    NUMPAD_9,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    F13,
    F14,
    F15,
    PAUSE
};

} // namespace key

//------------------------------------------------------------------------------
//                                   PROTOTYPES
//------------------------------------------------------------------------------

/** @return the mouse position */
glm::vec2 getMousePos();

/** @return if the given mouse button is being pressed */
bool mousePressed( mouse_button::Type button );

/** #Hidden
Sets the amount the mouse has scrolled this frame */
void setMouseScroll( int scroll );

/** @return the amount scrolled by the mouse wheel since the last frame */
int getMouseScroll();

/** Check if the given is being pressed
#NOTE: this does not take into consideration upper and lower case
@param key the key to check for
@return if the key is being pressed*/
bool isKeyPressed( key::Type key );

} // namespace input

} // namespace omi

#endif
