#include "Packs.hpp"

namespace pack
{

void buildEffectsPack()
{
    omi::ResourceManager::addMaterialGeometryMesh(
        "function_trail",
        resource_group::EFFECTS,
        "default_shader",
        glm::vec4( 1.0f, 0.0f, 1.0f, 0.0f ),
        "res/gfx/geometry/effects/function_trail.obj",
        1,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "func_explosion",
        resource_group::EFFECTS,
        "default_shader",
        glm::vec4( 1.0f, 0.0f, 1.0f, 0.0f ),
        "res/gfx/geometry/effects/function_explosion.obj",
        1,
        omi::material::SHADELESS
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "tower_explosion",
        resource_group::EFFECTS,
        "default_shader",
        glm::vec4( 1.0f, 0.5f, 0.2f, 0.0f ),
        "res/gfx/geometry/effects/tower_explosion.obj",
        1,
        omi::material::SHADELESS
    );

    //----------------------------------SOUNDS----------------------------------

    omi::ResourceManager::addSound(
        "fire_1",
        resource_group::EFFECTS,
        "res/sound/fx/gameplay/fire_1.ogg",
        1
    );

    omi::ResourceManager::addSound(
        "explode_1",
        resource_group::EFFECTS,
        "res/sound/fx/gameplay/explode_1.ogg",
        1
    );
}

} // namespace pack
