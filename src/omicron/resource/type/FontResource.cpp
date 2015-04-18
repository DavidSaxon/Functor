#include "FontResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

FontResource::FontResource(
        resource_group::ResourceGroup resourceGroup,
        FT_Library* freeType,
        const std::string& filePath )
    :
    Resource  ( resourceGroup ),
    m_freeType( freeType ),
    m_filePath( filePath )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void FontResource::load()
{
    if ( !m_loaded )
    {
        m_font = std::unique_ptr<Font>(
                loader::loadFontFromFile( m_freeType, m_filePath ) );
    }
    m_loaded = true;
}

void FontResource::release()
{
    if ( m_loaded )
    {
        m_font = std::unique_ptr<Font>( );
        m_loaded = false;
    }
}

Font* FontResource::get() const
{
    if ( !m_loaded )
    {
        std::cout << "attempted to get unloaded font" << std::endl;
        //TODO: throw an exception
    }

    return m_font.get();
}

} // namespace omi
