#include "Packs.hpp"

namespace pack
{

void buildEnvironmentPack()
{
    // world
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "world_std",
        resource_group::ENVIRONMENT,
        "default_shader",
        "res/gfx/texture/environment/world_std.png",
        "res/gfx/geometry/environment/world_std.obj",
        0
    );
}

} // namespace pack
