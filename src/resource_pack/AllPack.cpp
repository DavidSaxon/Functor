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

    // the title font of the reverie
    omi::ResourceManager::addFont(
        "title_font",
        resource_group::ALL,
        "res/gfx/fonts/semarang.otf"
    );
}

} // namespace pack
