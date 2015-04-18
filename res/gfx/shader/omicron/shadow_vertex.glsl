#version 130

// the model, view, projection matrix
uniform mat4 u_modelViewProjectionMatrix;

void main()
{
    // set the position
    gl_Position = u_modelViewProjectionMatrix * gl_Vertex;
}
