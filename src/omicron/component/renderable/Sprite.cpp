#include "Sprite.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Sprite::Sprite(
        const std::string& id,
              int          layer,
              Transform*   transform,
              Material     material,
        const glm::vec2&   size,
        const glm::vec2&   texSize,
        const glm::vec2&   texOffset )
    :
    Renderable ( id, layer, transform, material ),
    m_size     ( size ),
    m_half     ( size.x / 2.0f, size.y / 2.0f ),
    m_texSize  ( texSize ),
    m_texOffset( texOffset ),
    m_texCoord ( texOffset.x + texSize.x, texOffset.y + texSize.y )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

const glm::vec2& Sprite::getSize() const
{
    return m_size;
}

const glm::vec2& Sprite::getTexSize() const
{
    return m_texSize;
}

const glm::vec2& Sprite::getTexOffset() const
{
    return m_texOffset;
}

void Sprite::setSize( const glm::vec2& size )
{
    m_size = size;
    m_half.x = size.x / 2.0f;
    m_half.y = size.y / 2.0f;
}

void Sprite::setTexSize( const glm::vec2& texSize )
{
    m_texSize = texSize;
    m_texCoord.x = m_texOffset.x + m_texSize.x;
    m_texCoord.y = m_texOffset.y + m_texSize.y;
}

void Sprite::setTexOffset( const glm::vec2& texOffset )
{
    m_texOffset = texOffset;
    m_texCoord.x = m_texOffset.x + m_texSize.x;
    m_texCoord.y = m_texOffset.y + m_texSize.y;
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Sprite::draw()
{
    glBegin(GL_TRIANGLES);

        glTexCoord2f( m_texCoord.x, m_texCoord.y );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f(  m_half.x,  m_half.y, 0.0f );

        glTexCoord2f( m_texOffset.x, m_texCoord.y );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f( -m_half.x,  m_half.y, 0.0f );

        glTexCoord2f( m_texCoord.x, m_texOffset.y );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f(  m_half.x, -m_half.y, 0.0f );

        glTexCoord2f( m_texOffset.x, m_texOffset.y );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f( -m_half.x, -m_half.y, 0.0f );

        glTexCoord2f( m_texCoord.x, m_texOffset.y );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f(  m_half.x, -m_half.y, 0.0f );

        glTexCoord2f( m_texOffset.x, m_texCoord.y );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f( -m_half.x,  m_half.y, 0.0f );

    glEnd();
}

} // namespace omi
