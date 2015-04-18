#version 130

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

// the texture
uniform sampler2D u_texture;

//the texture coords
varying vec2 v_texCoord;

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main() {

    // get texture from look up
    vec4 texCol = texture2D( u_texture, v_texCoord );

    // filter out colours below threshold
    if ( texCol.r + texCol.g + texCol.b < 0.05 )
    {
        texCol.r = 1.0;
        texCol.g = 1.0;
        texCol.b = 1.0;
        texCol.a = 0.0;
    }

    gl_FragColor = texCol;
}
