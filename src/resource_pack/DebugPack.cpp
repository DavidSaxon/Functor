#include "Packs.hpp"

namespace pack {

void buildDebugPack()
{
    //-----------------------------------FONT-----------------------------------

    // debugging print outs font
    omi::ResourceManager::addFont(
        "debug_font",
        resource_group::DEBUG,
        "res/gfx/fonts/debug/clear_sans.ttf"
    );

    //-----------------------------------TEXT-----------------------------------

    // fps counter text
    omi::ResourceManager::addMaterialText(
        "fps_counter_text",
        resource_group::DEBUG,
        "default_shader",
        glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ),
        10,
        "debug_font",
        "0",
        0.15f,
        omi::material::SHADELESS
    );
}

} // namespace pack
