#version 130

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

//-----------------------------------UNIFORM------------------------------------

// the model, view, projection matrix
uniform mat4 u_modelViewProjectionMatrix;

//-----------------------------------VARYING------------------------------------

// the texture coords
varying vec2 v_texCoord;

//------------------------------------------------------------------------------
//                                 MAIN FUNCTION
//------------------------------------------------------------------------------

void main()
{
    //set the texture coords
    v_texCoord = vec2( gl_MultiTexCoord0 );

    //set the position
    gl_Position = u_modelViewProjectionMatrix * gl_Vertex;
}
