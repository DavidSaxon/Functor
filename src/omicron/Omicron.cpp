#include "Omicron.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

SystemSettings systemSettings;
DisplaySettings displaySettings;
RenderSettings renderSettings;
AudioSettings audioSettings;

FPSManager fpsManager;

FT_Library freeTypeLib;

bool omi_running = true;

glm::vec3 camScale;

bool omi_hasFocus = true;

} // namespace omi
