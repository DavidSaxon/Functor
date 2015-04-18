#version 130

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

// the texture
uniform sampler2D u_texture;

// the horizontal resolution
uniform float u_resolution;

//the texture coords
varying vec2 v_texCoord;

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main()
{
    // do nothing
    gl_FragColor = texture2D( u_texture, v_texCoord );;
}
