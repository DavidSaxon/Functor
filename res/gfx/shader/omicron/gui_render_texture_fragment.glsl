#version 130

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

// the texture
uniform sampler2D u_texture;
// the gamma value to use
uniform float u_gamma;

//the texture coords
varying vec2 v_texCoord;

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main()
{
    // get texture rgb colour
    vec4 col = texture2D( u_texture, v_texCoord );
    // apply gamma correction
    col = vec4( pow( col.rgb, vec3( 1.0 / u_gamma ) ), col.a );
    gl_FragColor = col;
}
