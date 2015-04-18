#include "Packs.hpp"

namespace pack
{

void buildPlayerPack()
{
    // TODO: REMOVE ME

    omi::ResourceManager::addMaterialGeometryMesh(
        "heretic_body",
        resource_group::PLAYER,
        "default_shader",
        glm::vec4( 0.2f, 0.2f, 0.2f, 1.0f ),
        "res/gfx/geometry/player/heretic_body.obj",
        0
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "heretic_turret",
        resource_group::PLAYER,
        "default_shader",
        glm::vec4( 0.2f, 0.2f, 0.2f, 1.0f ),
        "res/gfx/geometry/player/heretic_turret.obj",
        0
    );
}

} // namespace pack
