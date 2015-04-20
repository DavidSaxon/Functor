#include "Packs.hpp"

namespace pack
{

void buildEnvironmentPack()
{
    // world shader
    omi::ResourceManager::addShader(
        "world_shader",
        resource_group::ENVIRONMENT,
        "res/gfx/shader/gameplay/world_vertex.glsl",
        "res/gfx/shader/omicron/default_fragment.glsl"
    );

    // sun
    omi::ResourceManager::addMaterialGeometryMesh(
        "sun_std",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 1.0f, 1.0f, 0.75f, 1.0f ),
        "res/gfx/geometry/environment/sun.obj",
        0,
        omi::material::SHADELESS
    );

    // world
    omi::ResourceManager::addTextureMaterialGeometryMesh(
        "world_std",
        resource_group::ENVIRONMENT,
        "world_shader",
        "res/gfx/texture/environment/world_std.png",
        "res/gfx/geometry/environment/world_std.obj",
        0
    );

    // orbit 20
    omi::ResourceManager::addMaterialGeometryMesh(
        "orbit_20",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        "res/gfx/geometry/environment/orbit_20.obj",
        0,
        omi::material::SHADELESS
    );
    // orbit 30
    omi::ResourceManager::addMaterialGeometryMesh(
        "orbit_30",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        "res/gfx/geometry/environment/orbit_30.obj",
        0,
        omi::material::SHADELESS
    );
    // orbit 40
    omi::ResourceManager::addMaterialGeometryMesh(
        "orbit_40",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ),
        "res/gfx/geometry/environment/orbit_40.obj",
        0,
        omi::material::SHADELESS
    );

    // tower
    omi::ResourceManager::addMaterialGeometryMesh(
        "tower_base",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.3f, 0.3f, 0.3f, 1.0f ),
        "res/gfx/geometry/environment/tower_base.obj",
        0
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "tower1",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.3f, 0.3f, 1.0f, 1.0f ),
        "res/gfx/geometry/environment/tower1.obj",
        0
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "tower2",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.1f, 0.1f, 0.5f, 1.0f ),
        "res/gfx/geometry/environment/tower2.obj",
        0
    );

    omi::ResourceManager::addMaterialGeometryMesh(
        "tower3",
        resource_group::ENVIRONMENT,
        "default_shader",
        glm::vec4( 0.3f, 0.3f, 0.7f, 1.0f ),
        "res/gfx/geometry/environment/tower3.obj",
        0
    );
}

} // namespace pack
