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

//---------------------------BLUR FILTER MULTIPLIERS----------------------------

uniform float FILTER_OFFSET_0  = 0.06;
uniform float FILTER_OFFSET_1  = 0.06;
uniform float FILTER_OFFSET_2  = 0.06;
uniform float FILTER_OFFSET_3  = 0.06;
uniform float FILTER_OFFSET_4  = 0.06;
uniform float FILTER_OFFSET_5  = 0.06;
uniform float FILTER_OFFSET_6  = 0.06;
uniform float FILTER_OFFSET_7  = 0.06;
uniform float FILTER_OFFSET_8  = 0.06;

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main()
{
    // where we will store the final colour
    vec4 finalColour = vec4( 0.0, 0.0, 0.0, 0.0 );

    //-----------------------------APPLY GLOW BLUR------------------------------
    // the blur uses a filter that sums greater than one, this helps gives the
    // glow an overexposed feel
    //--------------------------------------------------------------------------

    // calculate the size of a pixel
    float pixelSize = 1.0 / u_resolution;

    // pixel under this one
    finalColour += texture2D( u_texture, v_texCoord ) * FILTER_OFFSET_0;



    // pixels to the right
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 1.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_1;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 2.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_2;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 3.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_3;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 4.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_4;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 5.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_5;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 6.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_6;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 7.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_7;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 8.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_8;

    // pixels to the left
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 1.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_1;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 2.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_2;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 3.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_3;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 4.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_4;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 5.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_5;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 6.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_6;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 7.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_7;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 8.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_8;

    // boost alpha
    finalColour.a = 1.0;

    //----------------------------APPLY FINAL COLOUR----------------------------
    gl_FragColor = finalColour;
}
