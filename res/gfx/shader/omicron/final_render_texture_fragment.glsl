#version 130

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

// the texture
uniform sampler2D u_texture;
// texture resolution
uniform vec2 u_resolution;
// aspect ration
uniform float u_aspect;
// random multiplier
uniform float u_randMul;
// the amount of film grain
uniform float u_filmGrain;

//the texture coords
varying vec2 v_texCoord;

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

// generates a pseudo random number
float rand( vec2 co )
{
    return fract( sin( dot( co.xy, vec2( 12.9898, 78.233 ) ) )
                                    * 43758.5453 * u_randMul );
}

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main() {

    // set colour
    vec4 texCol = texture2D( u_texture, v_texCoord );

    // apply film grain to output
    float noise = clamp( rand( v_texCoord ), 0.0, 1.0 );
    noise = ( noise * 2.0 ) - 1.0;
    noise *= u_filmGrain;
    texCol.r += noise;
    texCol.g += noise;
    texCol.b += noise;

    // set final colour
    gl_FragColor = texCol;
}
