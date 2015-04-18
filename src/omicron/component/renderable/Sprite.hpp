#ifndef OMICRON_COMPONENT_RENDERABLE_SPRITE_H_
#   define OMICRON_COMPONENT_RENDERABLE_SPRITE_H_

#include "src/omicron/component/renderable/Renderable.hpp"

namespace omi {

/********************************************************\
| A flat quad that is essentially considered as geometry |
\********************************************************/
class Sprite : public Renderable {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new sprite
    @param id the identifier of the component
    @param layer the render layer of the sprite
    @param transform a pointer to a transform to use for the spirte's position
    @param material the the material to use for sprite
    @param size the size of the sprite
    @param texSize the size of the sprite's texture co-ordinates
    @param texOffset the offset of the sprite's texture co-ordinates */
    Sprite(
            const std::string& id,
                  int          layer,
                  Transform*   transform,
                  Material     material,
            const glm::vec2&   size,
            const glm::vec2&   texSize,
            const glm::vec2&   texOffset );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** @return the size of the sprite */
    const glm::vec2& getSize() const;

    /** @return the size of the sprite's texture co-ordinates */
    const glm::vec2& getTexSize() const;

    /** @return the offset of the sprite's texture co-ordinates */
    const glm::vec2& getTexOffset() const;

    /** @param size the new size of the sprite */
    void setSize( const glm::vec2& size );

    /** @param texSize the new size of the sprite's texture co-ordinates */
    void setTexSize( const glm::vec2& texSize );

    /** @param texOffset the new offset of the sprite's texture co-ordinates */
    void setTexOffset( const glm::vec2& texOffset );

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    void draw();

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the size of the sprite
    glm::vec2 m_size;
    // short hand for half the size of the sprite (so we don't have to
    // calculate it every frame)
    glm::vec2 m_half;

    // the size of the sprite's texture co-ordinates
    glm::vec2 m_texSize;
    // the offset of the sprites' texture co-ordinates
    glm::vec2 m_texOffset;
    //short hand for the texture co-ordinates of the sprite (so we don't have to
    // calculate it every frame)
    glm::vec2 m_texCoord;
};

} // namespace omi

#endif
