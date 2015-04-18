#include "Loaders.hpp"

#include "src/omicron/resource/ResourceServer.hpp"

namespace omi {

namespace loader {

GLuint loadTexture( const std::string& filePath, bool clamp, bool showPixels )
{

    // open the file using the resource server
    VirtualFile file;
    ResourceServer::get( filePath, file );

    // TODO: need to get file type

    //--------------------------LOAD IMAGE USING DEVIL--------------------------


    // the id of the image we are loading
    ILuint imageId;

    // generate and bind the image
    ilGenImages( 1, &imageId );
    ilBindImage( imageId );

    // match the image origin to OpenGL's
    ilEnable( IL_ORIGIN_SET );
    ilOriginFunc( IL_ORIGIN_LOWER_LEFT );

    //load the image
    // ILboolean success = ilLoadImage( ( ILstring ) filePath.c_str() );
    ILboolean success = ilLoadL(
            IL_PNG,
            static_cast<void*>( file.getData() ),
            file.getSize()
    );

    // check that the image loaded successfully
    if( !success )
    {
        std::cout << "image load failed" << std::endl;

        // unrecognised format??

        //clean up
        ilBindImage( 0 );
        ilDeleteImages( 1, &imageId );
        // TODO: freak out
    }

    // check that the image actually contains some data
    void* data = ilGetData();
    if ( !data )
    {
        std::cout << "empty data! FUCK!" << std::endl;

        ilBindImage( 0 );
        ilDeleteImages( 1, &imageId );
        // TODO: freak out
    }

    //get the important parameters from the image
    int width  = ilGetInteger( IL_IMAGE_WIDTH );
    int height = ilGetInteger( IL_IMAGE_HEIGHT );
    int type   = ilGetInteger( IL_IMAGE_TYPE );
    int format = ilGetInteger( IL_IMAGE_FORMAT );


    //--------------------------CREATE OPENGL TEXTURE---------------------------


    // the id of the texture in OpenGL
    GLuint textureId;

    // generate and bind the texture
    glGenTextures( 1, &textureId );
    glBindTexture( GL_TEXTURE_2D, textureId );

    // set the pixel store parameters
    glPixelStorei( GL_UNPACK_SWAP_BYTES, GL_FALSE );
    glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
    glPixelStorei( GL_UNPACK_SKIP_PIXELS, 0 );
    glPixelStorei( GL_UNPACK_SKIP_ROWS, 0 );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

    // load the texture into OpenGL
    glTexImage2D( GL_TEXTURE_2D, 0, format, width,
                 height, 0, format, type, data );

    // build mip-maps
    gluBuild2DMipmaps(
        GL_TEXTURE_2D, format, width, height, format, type, data );

    // set clamps
    if ( clamp )
    {
        glTexParameteri(
                GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri(
                GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    }
    else
    {
        glTexParameteri(
                GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
        glTexParameteri(
                GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    }
    // set the filtering modes
    glTexParameteri(
        GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    if ( showPixels )
    {
        glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    }
    else
    {
        glTexParameteri(
            GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }


    //---------------------------RETURN THE OPENGL ID---------------------------


    return textureId;
}

Texture* textureFromImage(
    const std::string& filePath, bool clamp, bool showPixels )
{
    return new Texture( loadTexture( filePath, clamp, showPixels ) );
}

Texture* animationFromImage(
    const std::string& filePath, unsigned frameRate,
    bool repeat, unsigned begin, unsigned end,
    bool clamp, bool showPixels )
{
    // separate the filename and extension
    unsigned divider = filePath.find_last_of( '.' );
    std::string filename  = filePath.substr( 0, divider );
    std::string extension = filePath.substr( divider + 1, filePath.length() );

    // load each texture and insert into a list
    std::vector<GLuint> textures;
    for ( unsigned i = begin; i <= end; ++i )
    {
        // TODO: freak out if the file doesn't exist

        // create the texture name and load it
        std::stringstream ss;
        ss << filename << "." << i << "." << extension;

        textures.push_back( loadTexture( ss.str(), clamp, showPixels ) );
    }

    return new Animation( textures, frameRate, repeat );
}

} // namespace loader

} // namespace omi
