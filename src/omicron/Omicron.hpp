#ifndef OMICRON_OMICRON_H_
#   define OMICRON_OMICRON_H_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <ft2build.h>
#include FT_FREETYPE_H

#include "lib/glm/glm.hpp"

#include "src/omicron/logic/FPSManager.hpp"
#include "src/omicron/settings/AudioSettings.hpp"
#include "src/omicron/settings/DisplaySettings.hpp"
#include "src/omicron/settings/RenderSettings.hpp"
#include "src/omicron/settings/SystemSettings.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                GLOBAL VARIABLES
//------------------------------------------------------------------------------

//-----------------------------------SETTINGS-----------------------------------

// system settings
extern SystemSettings systemSettings;
// the display settings
extern DisplaySettings displaySettings;
// the render settings
extern RenderSettings renderSettings;
// the audio settings
extern AudioSettings audioSettings;

// the fps manager
extern FPSManager fpsManager;

// the font library
extern FT_Library freeTypeLib;

// is true while Omicron is running
extern bool omi_running;

// the scale of the current camera
extern glm::vec3 camScale;

// is true if the game has focus
extern bool omi_hasFocus;

} // namespace omi

#endif
