#include "Packs.hpp"

namespace pack {

void buildLoadingPack()
{
    //-----------------------------------TEXT-----------------------------------

    omi::ResourceManager::addMaterialText(
        "loading_text", resource_group::LOADING,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        0,
        "title_font",
        "Loading",
        0.25f
    );
}

} // namespace pack
