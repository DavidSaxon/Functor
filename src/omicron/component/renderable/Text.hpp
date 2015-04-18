#ifndef OMICRON_COMPONENT_RENDERABLE_TEXT_HPP_
#   define OMICRON_COMPONENT_RENDERABLE_TEXT_HPP_

#include <map>

#include "src/omicron/component/renderable/Renderable.hpp"
#include "src/omicron/rendering/shading/Font.hpp"

namespace omi {

/**********************************************************\
| Structure for storing the cached text glyph information. |
\**********************************************************/
struct CachedGlyph {
    GLuint textureId;
    float left;
    float top;
    float width;
    float rows;
    float advanceX;
    float advanceY;
};

/*******************************\
| Renders a string using a font |
\*******************************/
class Text : public Renderable {
public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates new text to be rendered
    @param id the identifier of the component
    @param layer the render layer of the text
    @param transform a pointer to a transform to use for the text's position
    @param material the material to use for the text
    @param font the font to use
    @param str the string to render
    @param size the size of the font in world space co-ordinates */
    Text(
            const std::string& id,
            int layer,
            Transform* transform,
            Material material,
            Font* font,
            const std::string& str,
            float size );

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Override */
    virtual void render(
            Camera* camera,
            Camera* shadowCamera,
            const LightData& lightData );

    // TODO: font selectable

    // TODO: font glow

    //---------------------------------GETTERS----------------------------------

    /** @return the font being used to render the text */
    Font* getFont() const;

    /** @return the string that is being rendered */
    const std::string& getString() const;

    /** @return the size of the font */
    float getSize() const;

    /** @return if the text is horizontally centered */
    bool getHorCentred() const;

    /** @return if the text if vertically centered */
    bool getVertCentred() const;

    //---------------------------------SETTERS----------------------------------

    /** @param font the new font to use for rendering the text */
    void setFont( Font* font );

    /** @param str the new string to render */
    void setString( const std::string& str );

    /** @param size the new size of the font */
    void setSize( float size );

    /** set whether the text will be horizontally centered */
    void setHorCentred( bool state );

    /** Sets whether the text will be vertically centered */
    void setVertCentred( bool state );

protected:

    //--------------------------------------------------------------------------
    //                         PROTECTED MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    // TODO: render selectable

    /** #Override */
    void setShader( const LightData& lightData, Camera* camera );

    /** #Override */
    void draw();

    /** Calculate the offset of the text */
    void calculateOffset();

    /** @returns a cached glyph for the given character */
    CachedGlyph* getGlyph( char c );


private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the font to use for rendering
    Font* m_font;
    // the string to render
    std::string m_str;
    // the size of the text
    float m_size;
    // is true if the text is horizontally centered
    bool m_horCentred;
    // is true if the text is vertically centered
    bool m_vertCentred;
    // the offset of the text
    glm::vec2 m_offset;

    // the current character to render
    char m_char;
    // the current glyph we are using
    CachedGlyph* m_glyph;

    // a map from characters to caches
    std::map<char, CachedGlyph> m_cache;
};

} // namespace omi

#endif
