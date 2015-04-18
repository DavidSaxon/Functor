#include "Text.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

Text::Text(
        const std::string& id,
        int layer,
        Transform* transform,
        Material material,
        Font* font,
        const std::string& str,
        float size )
    :
    Renderable   ( id, layer, transform, material ),
    m_font       ( font ),
    m_str        ( str ),
    m_size       ( size ),
    m_horCentred ( false ),
    m_vertCentred( false ),
    m_char       ( ' ' ),
    m_glyph      ( NULL )
{
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Text::render(
        Camera* camera,
        Camera* shadowCamera,
        const LightData& lightData )
{
    // TODO: this might need to be done elsewhere since glow passes will be
    // behind
    // update the material
    m_material.update();

    // only render if visible and there is a camera
    if ( !visible || !m_material.isVisible() || camera == NULL)
    {
        return;
    }

    applyTransformations();
    calculateMatrices( camera );

    // get the window dimension we will use for text sizing
    float unitDim = displaySettings.getSize().y;
    if ( displaySettings.getSize().y > displaySettings.getSize().x )
    {
        unitDim = displaySettings.getSize().x;
    }

    // set font size
    FT_Set_Pixel_Sizes(
            *m_font,
            0,
            static_cast<FT_UInt>( unitDim * m_size )
    );

    calculateOffset();

    // the position of the cursor
    float cursorPosX = 0.0f;
    float cursorPosY = 0.0f;
    // iterate over each letter and render
    for ( unsigned i = 0; i < m_str.length(); ++i )
    {
        // set the current character and get the glyph
        m_char = m_str[ i ];
        m_glyph = getGlyph( m_char );

        setShader( lightData, camera );

        // get the positioning data in pixels
        float left   = cursorPosX + m_glyph->left;
        float top    = cursorPosY + m_glyph->top;
        float width  = m_glyph->width;
        float height = m_glyph->rows;
        // convert to world space co-ordinates
        left  =  left / unitDim;
        top   =  top / unitDim;
        width =  width / unitDim;
        height = height / unitDim;

        // draw geometry
        glBegin( GL_TRIANGLES );

            glTexCoord2f( 1.0f, 0.0f );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glVertex3f( m_offset.x + left + width, m_offset.y + top, 0.0f );

            glTexCoord2f( 0.0f, 1.0f );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glVertex3f( m_offset.x + left, m_offset.y + top - height, 0.0f );

            glTexCoord2f( 1.0f, 1.0f );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glVertex3f( m_offset.x + left + width,
                        m_offset.y + top - height, 0.0f );

            glTexCoord2f( 0.0f, 1.0f );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glVertex3f( m_offset.x + left, m_offset.y + top - height, 0.0f );

            glTexCoord2f( 1.0f, 0.0f );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glVertex3f( m_offset.x + left + width, m_offset.y + top, 0.0f );

            glTexCoord2f( 0.0f, 0.0f );
            glNormal3f( 0.0f, 0.0f, 1.0f );
            glVertex3f( m_offset.x + left, m_offset.y + top, 0.0f );

        glEnd();

        // move the cursor
        cursorPosX += m_glyph->advanceX;
        cursorPosY += m_glyph->advanceY;
    }

    unsetShader();
}

//-----------------------------------GETTERS------------------------------------

Font* Text::getFont() const
{
    return m_font;
}

const std::string& Text::getString() const
{
    return m_str;
}

float Text::getSize() const
{
    return m_size;
}

bool Text::getHorCentred() const
{
    return m_horCentred;
}

bool Text::getVertCentred() const
{
    return m_vertCentred;
}

//-----------------------------------SETTERS------------------------------------

void Text::setFont( Font* font )
{
    m_font = font;
}

void Text::setString( const std::string& str )
{
    m_str = str;
}

void Text::setSize( float size )
{
    m_size = size;
}

void Text::setHorCentred( bool state )
{
    m_horCentred = state;
}

void Text::setVertCentred( bool state )
{
    m_vertCentred = state;
}

//------------------------------------------------------------------------------
//                           PROTECTED MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void Text::setShader( const LightData& lightData, Camera* camera )
{
    // get the OpenGL program
    GLuint program = m_material.shader.getProgram();
    // use the shader
    glUseProgram( program );

    // pass in the matrices to the shader
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelMatrix" ),
        1, GL_FALSE, &m_modelMatrix[0][0] );
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_viewMatrix" ),
        1, GL_FALSE, &m_viewMatrix[0][0] );
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewMatrix" ),
        1, GL_FALSE, &m_modelViewMatrix[0][0] );
    glUniformMatrix3fv(
        glGetUniformLocation( program, "u_normalMatrix" ),
        1, GL_FALSE, &m_normalMatrix[0][0] );
    glUniformMatrix4fv(
        glGetUniformLocation( program, "u_modelViewProjectionMatrix" ),
        1, GL_FALSE, &m_modelViewProjectionMatrix[0][0] );

    // pass in colour to the shader
    glUniform4f(
        glGetUniformLocation( program, "u_colour" ),
        m_material.colour.r,
        m_material.colour.g,
        m_material.colour.b,
        m_material.colour.a
    );

    // font texture
    glUniform1i( glGetUniformLocation( program, "u_hasTexture" ), 1 );
    glBindTexture( GL_TEXTURE_2D, m_glyph->textureId );
    glUniform1i( glGetUniformLocation( program, "u_invertTexCol" ), 1 );

    // pass in camera exposure
    glUniform1f(
        glGetUniformLocation( program, "u_exposure" ),
        camera->getExposure()
    );

    // TODO: this can be moved into a common function
    //--------------------------------------------------------------------------
    // lighting
    if ( m_material.isShadeless() )
    {
        // material is not affected by light
        glUniform1i( glGetUniformLocation( program, "u_shadeless" ), 1 );
    }
    else
    {
        // material is affected by light
        glUniform1i( glGetUniformLocation( program, "u_shadeless" ), 0 );

        // pass in ambient light
        glm::vec3 ambientLight =
            renderSettings.getAmbientColour() *
            renderSettings.getAmbientStrength();
        glUniform3f(
            glGetUniformLocation( program, "u_ambientLight" ),
            ambientLight.r, ambientLight.g, ambientLight.b
        );

        // the number of lights
        glUniform1i(
            glGetUniformLocation( program, "u_lightCount" ),
            lightData.types.size()
        );
        if ( lightData.types.size() > 0 )
        {
            // the types of lights
            glUniform1iv(
                glGetUniformLocation( program, "u_lightType" ),
                lightData.types.size(),
                &lightData.types[0]
            );
            // the positions of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightPos" ),
                lightData.types.size(),
                &lightData.positions[0]
            );
            // the rotations of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightRot" ),
                lightData.types.size(),
                &lightData.rotations[0]
            );
            // the colours of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightColour" ),
                lightData.types.size(),
                &lightData.colours[0]
            );
            // the attenuation of lights
            glUniform3fv(
                glGetUniformLocation( program, "u_lightAttenuation" ),
                lightData.types.size(),
                &lightData.attenuations[0]
            );
            // the arcs of lights
            glUniform2fv(
                glGetUniformLocation( program, "u_lightArc" ),
                lightData.types.size(),
                &lightData.arcs[0]
            );
        }
    }

    //--------------------------------PROPERTIES--------------------------------

    // specular property
    Specular* specular = m_material.specular;
    float shininess = 0.0f;
    glm::vec3 specularColour;
    if ( specular != NULL )
    {
        shininess = specular->getShininess();
        specularColour = specular->getColour();
    }
    glUniform1f(
        glGetUniformLocation( program, "u_shininess" ),
        shininess
    );
    glUniform3f(
        glGetUniformLocation( program, "u_specularColour" ),
        specularColour.r,
        specularColour.g,
        specularColour.b
    );
}

// NOT USED
void Text::draw()
{
    glBegin(GL_TRIANGLES);

        glTexCoord2f( 1.0f, 1.0f );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f(  m_offset.x + 1.0f, m_offset.y + 1.0f, 0.0f );

        glTexCoord2f( 0.0f, 1.0f );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f( m_offset.x - 1.0f, m_offset.y +  1.0f, 0.0f );

        glTexCoord2f( 1.0f, 0.0f );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f(  m_offset.x + 1.0f, m_offset.y - 1.0f, 0.0f );

        glTexCoord2f( 0.0f, 0.0f );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f( m_offset.x - 1.0f, m_offset.y - 1.0f, 0.0f );

        glTexCoord2f( 1.0f, 0.0f );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f(  m_offset.x + 1.0f, m_offset.y - 1.0f, 0.0f );

        glTexCoord2f( 0.0f, 1.0f );
        glNormal3f(  0.0f,      0.0f,     1.0f );
        glVertex3f( m_offset.x - 1.0f,  m_offset.y + 1.0f, 0.0f );

    glEnd();
}

void Text::calculateOffset()
{
    // clear the offset
    m_offset = glm::vec2( 0.0f, 0.0f );

    // get the window dimension we will use for text sizing
    float unitDim = displaySettings.getSize().y;
    if ( displaySettings.getSize().y > displaySettings.getSize().x )
    {
        unitDim = displaySettings.getSize().x;
    }

    // horizontal centering
    if ( m_horCentred )
    {
        // calculate the length of the text
        float length = 0.0f;
        for ( unsigned i = 0; i < m_str.length(); ++i )
        {
            char c = m_str[ i ];

            // get the character
            CachedGlyph* glyph = getGlyph( c );

            length += glyph->advanceX;
        }

        // calculate offset
        length /= unitDim;
        m_offset.x = -( length / 2.0f );
    }

    // vertical centering
    if ( m_vertCentred )
    {
        // get the character
        CachedGlyph* glyph = getGlyph( m_str[ 0 ] );

        m_offset.y = glyph->rows / unitDim;
        m_offset.y /= 2.0f;
        m_offset.y = -m_offset.y;
    }
}

CachedGlyph* Text::getGlyph( char c )
{
    // check if the glyph is in the cache
    if ( m_cache.find( c ) != m_cache.end() )
    {
        // return from the cache
        return &m_cache[ c ];
    }

    // create the cachable glyph
    CachedGlyph glyph;

    // create an OpenGL texture
    glGenTextures  ( 1, &glyph.textureId );
    glBindTexture  ( GL_TEXTURE_2D, glyph.textureId );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,     GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,     GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the free type glyph as a texture
    FT_Load_Char( *m_font, c, FT_LOAD_RENDER );
    glTexImage2D(
          GL_TEXTURE_2D,
          0,
          GL_ALPHA,
          (*m_font)->glyph->bitmap.width,
          (*m_font)->glyph->bitmap.rows,
          0,
          GL_ALPHA,
          GL_UNSIGNED_BYTE,
          (*m_font)->glyph->bitmap.buffer
    );

    // store the other glyph data we need
    glyph.left     = static_cast<float>( (*m_font)->glyph->bitmap_left  );
    glyph.top      = static_cast<float>( (*m_font)->glyph->bitmap_top   );
    glyph.width    = static_cast<float>( (*m_font)->glyph->bitmap.width );
    glyph.rows     = static_cast<float>( (*m_font)->glyph->bitmap.rows );
    glyph.advanceX = static_cast<float>( (*m_font)->glyph->advance.x >> 6 );
    glyph.advanceY = static_cast<float>( (*m_font)->glyph->advance.y >> 6 );

    // add to the cache
    m_cache.insert( std::make_pair( c, glyph ) );

    return &m_cache[ c ];
}

} // namespace omi
