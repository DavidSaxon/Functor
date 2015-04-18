#version 130

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

// the view matrix
uniform mat4 u_viewMatrix;

// the colour
uniform vec4 u_colour;
// if the material has a texture
uniform int u_hasTexture;
// the texture
uniform sampler2D u_texture;
// is true to invert texture colour
uniform int u_invertTexCol;

// shininess
uniform float u_shininess;
// specular colour
uniform vec3 u_specularColour;
// if there is a specular map
uniform int u_hasSpecMap;
// the specular map
uniform sampler2D u_specMap;

// if the material is shadeless
uniform int u_shadeless;

// the shadow map
uniform sampler2D u_shadowMap;
// the light casting shadows
uniform int u_shadowCaster;

// the exposure of the camera
uniform float u_exposure;

//the ambient light
uniform vec3 u_ambientLight;

// the number of lights
uniform int u_lightCount;
// the light types
uniform int u_lightType[8];
// the light positions
uniform vec3 u_lightPos[8];
// the light rotations
uniform vec3 u_lightRot[8];
// the light colours
uniform vec3 u_lightColour[8];
// the light attenuations
uniform vec3 u_lightAttenuation[8];
// the light arcs
uniform vec2 u_lightArc[8];
// the lights that are inversed
uniform int u_lightInverse[8];
// the lights that are ignored
uniform int u_lightIgnore[8];

//the texture coords
varying vec2 v_texCoord;
//the normal
varying vec3 v_normal;
// the eye position
varying vec3 v_eyePos;
// the shadow co-ordinates
varying vec4 v_shadowCoord;

vec2 poissonDisk[4] = vec2[](
    vec2( -0.94201624, -0.39906216 ),
    vec2( 0.94558609, -0.76890725 ),
    vec2( -0.094184101, -0.92938870 ),
    vec2( 0.34495938, 0.29387760 )
);

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main() {

    //---------------------------------MATERIAL---------------------------------

    // the colour of the material
    vec4 material = u_colour;

    //apply texturing
    vec4 textureColour = texture2D( u_texture, v_texCoord );
    if ( u_invertTexCol != 0 )
    {
        vec4 invertCol = vec4( 1.0, 1.0, 1.0, 1.0 ) - textureColour;
        invertCol.a = textureColour.a;
        textureColour = invertCol;
    }
    if ( u_hasTexture != 0 )
    {
        material *= textureColour;
    }

    //---------------------------------LIGHTING---------------------------------

    if ( u_shadeless != 0 )
    {
        gl_FragColor = material;
    }
    else
    {
        // the light value
        vec3 light = u_ambientLight;

        // normalize the normal
        vec3 N = normalize( v_normal );

        for ( int i = 0; i < u_lightCount; ++i )
        {
            // calculate shadowing
            float visibility = 1.0;
            if ( i == u_shadowCaster )
            {
                float shadowCosThetha = dot( N, normalize( u_lightPos[i] ) );
                shadowCosThetha = clamp( shadowCosThetha, 0.0, 1.0 );
                float bias = 0.000025 * tan( acos( shadowCosThetha ) );
                bias = clamp( bias, 0.0, 0.01 );
                if ( texture2D( u_shadowMap, v_shadowCoord.xy ).x <
                     v_shadowCoord.z - bias )
                {
                    visibility = 0.5;
                }
            }
            vec3 visiblityVec = vec3( visibility, visibility, visibility );

            // ignore this light
            if ( u_lightIgnore[i] != 0 )
            {
                // do nothing
            }
            // directional light
            else if ( u_lightType[i] == 0 )
            {
                // compute the light position
                vec3 lightDir = normalize( u_lightPos[i] );
                // compute angle between normal and light
                float cosThetha = max( dot( N, lightDir ), 0.0 );
                if ( cosThetha > 0.0 )
                {
                    // compute and add diffuse colour
                    light += u_lightColour[i] * cosThetha * visiblityVec;
                    // compute half vector
                    vec3 H =
                        normalize( normalize( v_eyePos ) +
                                   normalize( u_lightPos[i] ) );
                    // compute specular
                    float cosAlpha = max( dot( N, H ), 0.0 );
                    vec3 specular = u_specularColour * u_lightColour[i] *
                            pow( cosAlpha, u_shininess ) * visiblityVec;
                    if ( u_hasSpecMap > 0 )
                    {
                        specular *= texture2D( u_specMap, v_texCoord ).rgb;
                    }
                    light += specular;
                }
            }
            // point light
            else if ( u_lightType[i] == 1 )
            {
                // compute the light position
                vec3 lightDir = u_lightPos[i] + v_eyePos;
                // the distance to the light source
                float distance = length( lightDir );
                // compute angle between normal and light
                float cosThetha = max( dot( N, normalize( lightDir ) ), 0.0 );
                if ( cosThetha > 0.0 )
                {
                    // calculate attenuation
                    float attenuation = 1.0 / (
                        u_lightAttenuation[i].x +
                        ( u_lightAttenuation[i].y * distance ) +
                        ( u_lightAttenuation[i].z * distance * distance ) );
                    // apply diffuse
                    if ( u_lightInverse[i] == 1 )
                    {
                        light -= attenuation * u_lightColour[i] *
                                 cosThetha * visiblityVec;
                    }
                    else
                    {
                        light += attenuation * u_lightColour[i] *
                                 cosThetha * visiblityVec;
                    }
                    // compute half vector
                    vec3 H =
                        normalize( normalize( v_eyePos ) +
                                   normalize( lightDir ) );
                    // compute specular
                    float cosAlpha = max( dot ( N, H ), 0.0 );
                    vec3 specular = attenuation * u_specularColour *
                                     u_lightColour[i] *
                                    pow( cosAlpha, u_shininess ) * visiblityVec;
                    if ( u_hasSpecMap > 0 )
                    {
                        specular *= texture2D( u_specMap, v_texCoord ).rgb;
                    }

                    if ( u_lightInverse[i] != 1 )
                    {
                        light += specular;
                    }
                }
            }
            // spot light
            else if ( u_lightType[i] == 2 )
            {
                // compute the light position
                vec3 lightDir = u_lightPos[i] + v_eyePos;
                // the distance to the light source
                float distance = length( lightDir );
                // compute angle between normal and light
                float cosThetha = max( dot( N, normalize( lightDir ) ), 0.0 );
                if ( cosThetha > 0.0 )
                {
                    // calculate the spot light effect
                    float spotEffect =
                        dot( normalize( u_lightRot[i] ),
                             normalize( -lightDir ) );
                    if ( spotEffect > u_lightArc[i].x )
                    {
                        spotEffect = smoothstep( u_lightArc[i].x, u_lightArc[i].y, spotEffect );
                        // calculate attenuation
                        float attenuation = spotEffect / (
                            u_lightAttenuation[i].x +
                            ( u_lightAttenuation[i].y * distance ) +
                            ( u_lightAttenuation[i].z * distance * distance ) );
                        // apply diffuse
                        light += attenuation * u_lightColour[i] *
                                 cosThetha * visiblityVec;
                        // compute half vector
                        vec3 H =
                            normalize( normalize( v_eyePos ) +
                                        normalize( lightDir ) );
                        // compute specular
                        float cosAlpha = max( dot ( N, H ), 0.0 );
                        vec3 specular = attenuation * u_specularColour *
                                u_lightColour[i] *
                                pow( cosAlpha, u_shininess ) * visiblityVec;
                        {
                            specular *= texture2D( u_specMap, v_texCoord ).rgb;
                        }
                        light += specular;
                    }
                }
            }
        }

        vec4 finalColour = material * vec4( light, 1.0 );
        finalColour = vec4(
            1.0 - exp( -u_exposure * finalColour.rgb ),
            finalColour.a
        );
        gl_FragColor = finalColour;

    }
}
