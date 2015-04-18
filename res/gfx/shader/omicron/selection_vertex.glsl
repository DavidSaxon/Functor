#version 130

// the model, view, projection matrix
uniform mat4 u_modelViewProjectionMatrix;
// texture co-ordinates
varying vec2 v_texCoord;

void main()
{
    v_texCoord = vec2( gl_MultiTexCoord0 );
    gl_Position = u_modelViewProjectionMatrix * gl_Vertex;
}
