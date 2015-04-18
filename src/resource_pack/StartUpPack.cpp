#include "Packs.hpp"

#include "src/data/layers/StartUpLayers.hpp"

namespace pack {

void buildStartUpPack()
{
    //---------------------------------SPRITES----------------------------------

    // omicron logo text bottom
    omi::ResourceManager::addTextureMaterialSprite(
        "omicron_text_bottom", resource_group::START_UP,
        "default_shader",
        "res/gfx/texture/start_up/omicron/logo_text_bottom.png",
        layer::start_up::OMICRON_MAIN_TEXT,
        glm::vec2( 2, 2 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );
    // omicron logo text top
    omi::ResourceManager::addTextureMaterialSprite(
        "omicron_text_top", resource_group::START_UP,
        "default_shader",
        "res/gfx/texture/start_up/omicron/logo_text_top.png",
        layer::start_up::OMICRON_MAIN_TEXT,
        glm::vec2( 2, 2 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );
    // omicron long lens flare
    omi::ResourceManager::addTextureMaterialSprite(
        "omicron_flare_long", resource_group::START_UP,
        "default_shader",
        "res/gfx/texture/start_up/omicron/logo_flare_long.png",
        layer::start_up::OMICRON_LONG_LENS_FLARE,
        glm::vec2( 2, 2 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );
    // omicron centre lens flare
    omi::ResourceManager::addTextureMaterialSprite(
        "omicron_flare_centre", resource_group::START_UP,
        "default_shader",
        "res/gfx/texture/start_up/omicron/logo_flare_centre.png",
        layer::start_up::OMICRON_CENTRE_LENS_FLARE,
        glm::vec2( 2, 2 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );
    // omicron glow
    omi::ResourceManager::addTextureMaterialSprite(
        "omicron_glow", resource_group::START_UP,
        "default_shader",
        "res/gfx/texture/start_up/omicron/logo_glow.png",
        layer::start_up::OMICRON_TEXT_GLOW,
        glm::vec2( 2, 2 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );
    // omicron powered by text
    omi::ResourceManager::addTextureMaterialSprite(
        "omicron_powered_by", resource_group::START_UP,
        "default_shader",
        "res/gfx/texture/start_up/omicron/logo_powered_by.png",
        layer::start_up::OMICRON_MINOR_TEXT,
        glm::vec2( 2, 2 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );

    //----------------------------------SOUNDS----------------------------------

    omi::ResourceManager::addSound(
        "omicron_intro", resource_group::START_UP,
        "res/sound/fx/start_up/omicron_intro.ogg", 1
    );
}


} // namespace pack
