#ifndef OMICRON_RENDERING_LIGHTING_LIGHTDATA_HPP_
#   define OMICRON_RENDERING_LIGHTING_LIGHTDATA_HPP_

#define GLM_FORCE_RADIANS
#define GLM_SWIZZLE

#include <GL/glew.h>
#include <SFML/OpenGL.hpp>
#include <string>
#include <vector>

#include "lib/glm/glm.hpp"
#include "lib/glm/gtx/transform.hpp"

namespace omi {

/*****************************************************\
| Structure that contains packed data for all lights. |
\*****************************************************/
struct LightData {
    // the name of the light
    std::vector<std::string> names;
    // the light type
    std::vector<int> types;
    // the positions of the lights in eye space
    std::vector<float> positions;
    // the rotations of the lights
    std::vector<float> rotations;
    // the colour of the lights
    std::vector<float> colours;
    // the attenuation of the lights
    std::vector<float> attenuations;
    // the arcs of the lights
    std::vector<float> arcs;
    // the inverse states of the light
    std::vector<int> inverses;
    // the shadow map
    GLuint shadowMap;
    // the index of the light casting shadows
    int shadowCaster;

};

} // namespace omi

#endif
