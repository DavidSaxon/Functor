#version 130

// the colour
uniform vec4 u_colour;
// if the material has a texture
uniform int u_hasTexture;
// the texture
uniform sampler2D u_texture;
//the texture coords
varying vec2 v_texCoord;

void main()
{
    // the final colour
    vec4 finalColour = u_colour;
    vec4 textureColour = texture2D( u_texture, v_texCoord );
    if ( u_hasTexture > 0 )
    {
        finalColour.a = textureColour.a;
    }
    gl_FragColor = finalColour;
}
