#include "Packs.hpp"

#include "src/data/layers/GUILayers.hpp"

namespace pack {

void buildMenuPack()
{
    // pause menu overlay
    omi::ResourceManager::addMaterialSprite(
            "pause_menu_overlay",
            resource_group::MENU,
            "default_shader",
            glm::vec4( 0.0f, 0.0f, 0.0f, 0.25f ),
            layer::gui::PAUSE_OVERLAY,
            glm::vec2( 10.0f, 10.0f ),
            glm::vec2( 1.0f, 1.0f ),
            glm::vec2( 0.0f, 0.0f ),
            omi::material::SHADELESS
    );

    // pause main item text
    omi::ResourceManager::addMaterialText(
        "pause_main_item_text",
        resource_group::MENU,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        layer::gui::MAIN_MENU_ITEM,
        "title_font",
        "",
        0.2f,
        omi::material::SHADELESS
    );

    // pause secondary item text
    omi::ResourceManager::addMaterialText(
        "pause_secondary_item_text",
        resource_group::MENU,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        layer::gui::MAIN_MENU_ITEM,
        "title_font",
        "",
        0.1f,
        omi::material::SHADELESS
    );

    // enum widget arrow
    omi::ResourceManager::addTextureMaterialSprite(
        "enum_widget_arrow",
        resource_group::MENU,
        "default_shader",
        "res/gfx/texture/menu/enum_widget_arrow.png",
        layer::gui::WIDGET_PRIMARY,
        glm::vec2( 0.08, 0.08 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );

    // slider widget bar
    omi::ResourceManager::addTextureMaterialSprite(
        "slider_widget_bar",
        resource_group::MENU,
        "default_shader",
        "res/gfx/texture/menu/slider_widget_bar.png",
        layer::gui::WIDGET_PRIMARY,
        glm::vec2( 0.65, 0.65 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );

    // slider widget arrow
    omi::ResourceManager::addTextureMaterialSprite(
        "slider_widget_arrow",
        resource_group::MENU,
        "default_shader",
        "res/gfx/texture/menu/slider_widget_arrow.png",
        layer::gui::WIDGET_SECONDARY,
        glm::vec2( 0.08, 0.08 ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );
}

} // namespace pack
