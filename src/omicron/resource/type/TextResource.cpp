#include "TextResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

TextResource::TextResource(
        resource_group::ResourceGroup resourceGroup,
        int layer,
        const std::string& material,
        const std::string& font,
        const std::string& str,
        float size )
    :
    Resource  ( resourceGroup ),
    m_layer   ( layer),
    m_material( material ),
    m_font    ( font ),
    m_str     ( str ),
    m_size    ( size )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TextResource::load()
{
    if ( !m_loaded )
    {
        // text doesn't really need to load
        m_loaded = true;
    }
}

void TextResource::release()
{
    if ( m_loaded )
    {
        // likewise they don't need to be delete
        m_loaded = false;
    }
}

Text* TextResource::get( const std::string& id, Transform* transform ) const
{
    if ( !m_loaded )
    {
        std::cout << "attempted to get unloaded text" << std::endl;
        //TODO: throw an exception
    }

    // create a new text object
    return new Text(
        id, m_layer, transform,
        ResourceManager::getMaterial( m_material ),
        ResourceManager::getFont( m_font ),
        m_str,
        m_size
    );
}

} // namespace omi
