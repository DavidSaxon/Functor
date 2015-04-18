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

uniform float FILTER_OFFSET_0  = 1.0;
uniform float FILTER_OFFSET_1  = 0.6;
uniform float FILTER_OFFSET_2  = 0.36;
uniform float FILTER_OFFSET_3  = 0.216;
uniform float FILTER_OFFSET_4  = 0.1296;
uniform float FILTER_OFFSET_5  = 0.07776;
uniform float FILTER_OFFSET_6  = 0.046656;
uniform float FILTER_OFFSET_7  = 0.0279936;
uniform float FILTER_OFFSET_8  = 0.01679616;
uniform float FILTER_OFFSET_9  = 0.010077696;
uniform float FILTER_OFFSET_10 = 0.0060466176;
uniform float FILTER_OFFSET_11 = 0.00362797056;
uniform float FILTER_OFFSET_12 = 0.002176782336;
uniform float FILTER_OFFSET_13 = 0.0013060694016;
uniform float FILTER_OFFSET_14 = 0.00078364164096;
uniform float FILTER_OFFSET_15 = 0.000470184984576;
uniform float FILTER_OFFSET_16 = 0.000282110990746;
uniform float FILTER_OFFSET_17 = 0.000169266594447;
uniform float FILTER_OFFSET_18 = 0.000101559956668;
uniform float FILTER_OFFSET_19 = 0.000060935974001;
uniform float FILTER_OFFSET_20 = 0.0000365615844006;
uniform float FILTER_OFFSET_21 = 0.0000219369506404;
uniform float FILTER_OFFSET_22 = 0.0000131621703842;
uniform float FILTER_OFFSET_23 = 0.00000789730223054;
uniform float FILTER_OFFSET_24 = 0.00000473838133832;


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
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 9.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_9;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 10.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_10;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 11.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_11;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 12.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_12;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 13.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_13;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 14.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_14;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 15.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_15;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 16.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_16;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 17.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_17;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 18.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_18;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 19.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_19;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 20.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_20;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 21.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_21;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 22.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_22;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 23.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_23;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x - 24.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_24;

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
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 9.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_9;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 10.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_10;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 11.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_11;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 12.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_12;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 13.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_13;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 14.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_14;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 15.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_15;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 16.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_16;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 17.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_17;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 18.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_18;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 19.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_19;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 20.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_20;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 21.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_21;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 22.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_22;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 23.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_23;
    finalColour += texture2D( u_texture,
                   vec2( v_texCoord.x + 24.0 * pixelSize, v_texCoord.y ) ) *
                   FILTER_OFFSET_24;

    // boost alpha
    finalColour.a = 1.0;

    //----------------------------APPLY FINAL COLOUR----------------------------
    gl_FragColor = finalColour;
}
