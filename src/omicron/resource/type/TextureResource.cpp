#include "TextureResource.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTORS
//------------------------------------------------------------------------------

TextureResource::TextureResource(
              resource_group::ResourceGroup resourceGroup,
        const std::string&                  filePath,
              unsigned                      flags )
    :
    Resource    ( resourceGroup ),
    m_type      ( tex::TEXTURE ),
    m_filePath  ( filePath ),
    m_flags     ( flags ),
    m_clamp     ( false ),
    m_showPixels( false )
{
    parseFlags();
}

TextureResource::TextureResource(
              resource_group::ResourceGroup resourceGroup,
        const std::string&                  filePath,
              unsigned                      frameRate,
              bool                          repeat,
              unsigned                      begin,
              unsigned                      end,
              unsigned                      flags )
    :
    Resource    ( resourceGroup ),
    m_type      ( tex::ANIMATION ),
    m_filePath  ( filePath ),
    m_frameRate ( frameRate ),
    m_repeat    ( repeat ),
    m_begin     ( begin ),
    m_end       ( end ),
    m_flags     ( flags ),
    m_clamp     ( false ),
    m_showPixels( false )
{
    parseFlags();
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TextureResource::load()
{
    if ( !m_loaded )
    {
        switch ( m_type )
        {
            case tex::TEXTURE:
            {
                m_texture = std::unique_ptr<Texture>(
                    loader::textureFromImage(
                        m_filePath, m_clamp, m_showPixels
                    )
                );
                break;
            }
            case tex::ANIMATION:
            {
                m_texture = std::unique_ptr<Texture>(
                    loader::animationFromImage(
                        m_filePath, m_frameRate, m_repeat,
                        m_begin, m_end, m_clamp, m_showPixels
                    )
                );
                break;
            }
        }
        m_loaded = true;
    }
}

void TextureResource::release()
{
    if ( m_loaded )
    {
        GLuint id = m_texture->getId();
        glDeleteTextures( 1, &id );
        m_texture = std::unique_ptr<Texture>();
        m_loaded = false;
    }
}

Texture* TextureResource::get() const
{
    if ( !m_loaded )
    {
        std::cout << "attempted to get unloaded texture" << std::endl;

        //TODO: throw an exception
    }

    //copy the texture based on type
    Texture* tex;
    if ( m_texture->getType() == tex::ANIMATION )
    {
        tex = new Animation( *dynamic_cast<Animation*>( m_texture.get() ) );
    }
    else
    {
        tex = new Texture( *m_texture.get() );
    }

    return tex;
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void TextureResource::parseFlags()
{
    m_clamp      = (m_flags & texture::CLAMP       ) != 0;
    m_showPixels = (m_flags & texture::SHOW_PIXELS ) != 0;
}

} // namespace omi
