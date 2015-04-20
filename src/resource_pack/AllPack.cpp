#include "Packs.hpp"

namespace pack {

void buildAllPack()
{
    //---------------------------------SHADERS----------------------------------

    // default shader
    omi::ResourceManager::addShader(
        "default_shader",
        resource_group::ALL,
        "res/gfx/shader/omicron/default_vertex.glsl",
        "res/gfx/shader/omicron/default_fragment.glsl"
    );

    //-----------------------------------FONT-----------------------------------

    // the title font
    omi::ResourceManager::addFont(
        "title_font",
        resource_group::ALL,
        "res/gfx/fonts/courier_new.ttf"
    );

    omi::ResourceManager::addFont(
        "math_font",
        resource_group::ALL,
        "res/gfx/fonts/courier_new.ttf"
    );
}

} // namespace pack
