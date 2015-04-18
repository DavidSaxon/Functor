#include "Loaders.hpp"

#include <cstring>

#include "src/omicron/resource/ResourceServer.hpp"

namespace omi {

namespace loader {

Font* loadFontFromFile(
    FT_Library* freeType,
    const std::string& filePath )
{
    Font* font = new Font();

    // open the file using the resource server
    VirtualFile file;
    ResourceServer::get( filePath, file );

    // this needs to be in a newly allocated buffer since free type wants
    // ownership of it
    char* fileBuffer = ( char* ) malloc( sizeof( char ) * ( file.getSize() ) );
    for ( unsigned i = 0; i < file.getSize(); ++i )
    {
        fileBuffer[ i ] = file.getData()[ i ];
    }

    int result = FT_New_Memory_Face(
        *freeType,
        reinterpret_cast<const FT_Byte*>( fileBuffer ),
        file.getSize(),
        0,
        font
    );

    if( result != 0 )
    {
        // TODO: throw exception
        std::cout << "failed to load font: " << result << std::endl;
    }
    FT_Set_Pixel_Sizes( *font, 0, 14 );

    return font;
}

} // namespace loader

} // namespace omi
