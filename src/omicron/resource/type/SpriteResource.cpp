#include "SpriteResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

SpriteResource::SpriteResource(
              resource_group::ResourceGroup resourceGroup,
              int                           layer,
        const std::string&                  material,
        const glm::vec2&                    size,
        const glm::vec2&                    texSize,
        const glm::vec2&                    texOffset )
    :
    Resource   ( resourceGroup ),
    m_layer    ( layer ),
    m_material ( material ),
    m_size     ( size ),
    m_texSize  ( texSize ),
    m_texOffset( texOffset )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void SpriteResource::load()
{
    if ( !m_loaded )
    {
        // sprites don't really need to load
        m_loaded = true;
    }
}

void SpriteResource::release()
{
    if ( m_loaded )
    {
        // likewise they don't need to be delete
        m_loaded = false;
    }
}

Sprite* SpriteResource::get(
        const std::string& id, Transform* transform ) const
{
    if ( !m_loaded )
    {
        std::cout << "attempted to get unloaded sprite" << std::endl;

        //TODO: throw an exception
    }

    // create the sprite at the last minute
    return new Sprite(
        id, m_layer, transform,
        ResourceManager::getMaterial( m_material ),
        m_size, m_texSize, m_texOffset
    );
}


} // namespace omi
