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
    // the colour of the material
    vec4 material = u_colour;

    //apply texturing
    vec4 textureColour = texture2D( u_texture, v_texCoord );
    if ( u_hasTexture != 0 )
    {
        material *= textureColour;
    }

    gl_FragColor = material;
}
