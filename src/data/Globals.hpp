#ifndef HERETIC_DATA_GLOBALS_HPP_
#   define HERETIC_DATA_GLOBALS_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include "lib/glm/glm.hpp"

#include "src/omicron/input/Input.hpp"

/***********************************************\
| Variables that can be accessed by any object. |
\***********************************************/
namespace global {

// is true if reverie is paused
extern bool pause;

//-----------------------------------SETTINGS-----------------------------------

// the master volume for all sounds
extern float masterVolume;

// the look sensitivity multiplier
extern float lookSensitivity;
// the key bindings
extern omi::input::key::Type keyForwards;
extern omi::input::key::Type keyBackwards;
extern omi::input::key::Type keyLeft;
extern omi::input::key::Type keyRight;

//----------------------------------MENU STYLE----------------------------------

// the colour of a selected menu item
extern const glm::vec4 MENU_ITEM_SELECTED_COLOUR;
// the colour of a non-selected menu item
extern const glm::vec4 MENU_ITEM_NON_SELECTED_COLOUR;

//-------------------------------------GUI--------------------------------------

extern const float FUNC_BOX_SIZE;

//-----------------------------------GAMEPLAY-----------------------------------

extern bool m_inOrbit;

} // namespace global

#endif
