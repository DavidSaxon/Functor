#ifndef OMICRON_RESOURCE_TYPE_SPRITE_RESOURCE_H_
#   define OMICRON_RESOURCE_TYPE_SPRITE_RESOURCE_H_

#include "src/omicron/resource/ResourceManager.hpp"

class ResourceManager;

#include "src/omicron/component/renderable/Sprite.hpp"
#include "src/omicron/resource/type/Resource.hpp"

namespace omi {

/********************************************\
| Contains the needed data to load a sprite. |
\********************************************/
class SpriteResource : public Resource {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a sprite resource
    @param resourceGroup the resource group of the sprite
    @param layer the layer of sprite
    @param material the resource id of the sprite's material
    @param size the size of the sprite
    @param texSize the size of the sprite's texture co-ordinates
    @param texOffset the offset of the sprite's texture co-ordinates */
    SpriteResource(
              resource_group::ResourceGroup resourceGroup,
              int                           layer,
        const std::string&                  material,
        const glm::vec2&                    size,
        const glm::vec2&                    texSize,
        const glm::vec2&                    texOffset );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void load();

    /** #Override */
    void release();

    /** @return the loaded sprite
    @param id the component identifier of the sprite
    @param transform the transform to use for the sprite*/
    Sprite* get( const std::string& id, Transform* transform ) const;

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the layer of the sprite
    int m_layer;
    // the resource id of the sprite's material
    std::string m_material;
    // the size of the sprite
    glm::vec2 m_size;
    // the size of the sprite's texture co-ordinates
    glm::vec2 m_texSize;
    // the offset of the sprite's texture co-ordinates
    glm::vec2 m_texOffset;
};

} // namespace omi

#endif
