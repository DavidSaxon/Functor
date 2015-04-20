#include "Packs.hpp"

#include "src/data/Globals.hpp"
#include "src/data/layers/GUILayers.hpp"

namespace pack
{

void buildGUIPack()
{
    // intro
    omi::ResourceManager::addTextureMaterialSprite(
        "intro_info",
        resource_group::GUI,
        "default_shader",
        "res/gfx/texture/gui/story.png",
        layer::gui::FUCK_YOU,
        glm::vec2( 1.98f, 1.98f ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );
    omi::ResourceManager::addMaterialText(
        "intro_title",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f ),
        layer::gui::FUCK_YOU,
        "math_font",
        "FUNCTOR:",
        0.4f,
        omi::material::SHADELESS
    );
    omi::ResourceManager::addMaterialText(
        "intro_sub_title",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 0.0f ),
        layer::gui::FUCK_YOU,
        "math_font",
        "An Unconventional Weapon",
        0.1f,
        omi::material::SHADELESS
    );

    // target
    omi::ResourceManager::addTextureMaterialSprite(
        "gui_target",
        resource_group::GUI,
        "default_shader",
        "res/gfx/texture/gui/target.png",
        layer::gui::FUNCTION_BACK,
        glm::vec2( 0.1f, 0.1f ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0, omi::material::SHADELESS
    );


    // function box
    omi::ResourceManager::addMaterialSprite(
            "gui_function_box",
            resource_group::GUI,
            "default_shader",
            glm::vec4( 0.0f, 0.0f, 0.0f, 0.5f ),
            layer::gui::FUNCTION_BACK,
            glm::vec2( global::FUNC_BOX_SIZE, global::FUNC_BOX_SIZE / 2.0f ),
            glm::vec2( 1.0f, 1.0f ),
            glm::vec2( 0.0f, 0.0f ),
            omi::material::SHADELESS
    );

    // function text
    omi::ResourceManager::addMaterialText(
        "gui_function_text",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
        layer::gui::FUNCTION_TEXT,
        "math_font",
        "",
        0.08f,
        omi::material::SHADELESS
    );

    // multiplier text
    omi::ResourceManager::addMaterialText(
        "gui_mul_text",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        layer::gui::FUNCTION_TEXT,
        "math_font",
        "",
        0.08f,
        omi::material::SHADELESS
    );

    // reload bar
    omi::ResourceManager::addMaterialSprite(
            "gui_reload_back",
            resource_group::GUI,
            "default_shader",
            glm::vec4( 0.0f, 0.0f, 0.0f, 0.5f ),
            layer::gui::FUNCTION_BACK,
            glm::vec2( global::FUNC_BOX_SIZE * 2.0f, 0.05f ),
            glm::vec2( 1.0f, 1.0f ),
            glm::vec2( 0.0f, 0.0f ),
            omi::material::SHADELESS
    );
    omi::ResourceManager::addMaterialSprite(
            "gui_reload_front",
            resource_group::GUI,
            "default_shader",
            glm::vec4( 1.0f, 1.0f, 1.0f, 1.0f ),
            layer::gui::FUNCTION_TEXT,
            glm::vec2( global::FUNC_BOX_SIZE * 2.0f, 0.05f ),
            glm::vec2( 1.0f, 1.0f ),
            glm::vec2( 0.0f, 0.0f ),
            omi::material::SHADELESS
    );


    // world index
    omi::ResourceManager::addMaterialText(
        "world_index_text",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        3,
        "title_font",
        "1: EASY",
        1.0f,
        omi::material::SHADELESS
    );

    // world index
    omi::ResourceManager::addMaterialText(
        "level_select_help",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        layer::gui::HELP,
        "math_font",
        "",
        0.07f,
        omi::material::SHADELESS
    );


    omi::ResourceManager::addMaterialText(
        "condition",
        resource_group::GUI,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        layer::gui::FUCK_YOU,
        "math_font",
        "",
        0.4f,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialSprite(
        "func_tut",
        resource_group::GUI,
        "default_shader",
        "res/gfx/texture/gui/func_tut.png",
        layer::gui::HELP,
        glm::vec2( 0.7f, 0.7f ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialSprite(
        "destroy_tut",
        resource_group::GUI,
        "default_shader",
        "res/gfx/texture/gui/destroy_tut.png",
        layer::gui::HELP,
        glm::vec2( 0.7f, 0.7f ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialSprite(
        "win_tut",
        resource_group::GUI,
        "default_shader",
        "res/gfx/texture/gui/win_tut.png",
        layer::gui::HELP,
        glm::vec2( 0.7f, 0.7f ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addTextureMaterialSprite(
        "exit_tut",
        resource_group::GUI,
        "default_shader",
        "res/gfx/texture/gui/exit_tut.png",
        layer::gui::HELP,
        glm::vec2( 0.7f, 0.7f ),
        glm::vec2( 1, 1 ),
        glm::vec2( 0, 0 ),
        0,
        omi::material::SHADELESS
    );
}

} // namespace pack
