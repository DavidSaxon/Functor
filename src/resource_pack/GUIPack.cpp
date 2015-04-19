#include "Packs.hpp"

#include "src/data/Globals.hpp"
#include "src/data/layers/GUILayers.hpp"

namespace pack
{

void buildGUIPack()
{
    // function box
    omi::ResourceManager::addMaterialSprite(
            "gui_function_box",
            resource_group::GUI,
            "default_shader",
            glm::vec4( 0.0f, 0.0f, 0.0f, 0.75f ),
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
}

} // namespace pack
