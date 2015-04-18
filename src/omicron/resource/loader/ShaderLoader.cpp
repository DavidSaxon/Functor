#include "Loaders.hpp"

#include "src/omicron/resource/ResourceServer.hpp"

namespace omi {

namespace loader {

Shader loadShaderFromFiles(
        const std::string& vertexPath,
        const std::string& fragmentPath) {

    // create the shader and program objects
    GLuint program        = glCreateProgram();
    GLuint vertexShader   = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // get the files as character strings from the server
    VirtualFile vertexFile;
    ResourceServer::get( vertexPath, vertexFile );
    const GLchar* vertexSource =
            reinterpret_cast<const GLchar*>( vertexFile.getData() );
    VirtualFile fragFile;
    ResourceServer::get( fragmentPath, fragFile );
    const GLchar* fragmentSource =
            reinterpret_cast<const GLchar*>( fragFile.getData() );

    // load shader source code into OpenGL
    glShaderSource(vertexShader,   1, &vertexSource,   NULL);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);

    // compile the vertex shader
    glCompileShader(vertexShader);
    // int vLength = 0;
    // int vMaxLength;
    // glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &vMaxLength);
    // char vertexInfoLog[vMaxLength];
    // glGetShaderInfoLog(vertexShader, vMaxLength, &vLength, vertexInfoLog);

    // compile the fragment shader
    glCompileShader(fragmentShader);

    // attach the shaders to the program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // link the program
    glLinkProgram(program);

    // check to make sure the shaders have compiled correctly
    GLint result;
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (result == GL_FALSE) {

        GLint length;
        char* log;

        // get the program info log
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        log = new char[length];
        glGetProgramInfoLog(program, length, &result, log);

        std::cout << "error compiling shader: " << std::endl;
        std::cout << "vertex:   " << vertexPath << std::endl;
        std::cout << "fragment: " << fragmentPath << std::endl;
        std::cout << "error Log:" << std::endl;
        std::cout << log << std::endl;

        // clean up
        glDeleteProgram(program);
        program = 0;

        // TODO: freak out and throw an exception
    }

    return Shader(vertexShader, fragmentShader, program);
}

} // namespace loader

} // namespace omi
