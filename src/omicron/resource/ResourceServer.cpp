#include "ResourceServer.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                   VARIABLES
//------------------------------------------------------------------------------

bool ResourceServer::m_loadFromLibrary = true;
std::map<std::string, unsigned long> ResourceServer::m_libStarts;
std::map<std::string, unsigned long> ResourceServer::m_libEnds;

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void ResourceServer::init()
{
    // open the resource library header
    std::ifstream file( "resources.omi_h" );

    // iterate over the file
    while( file.good() )
    {
        // get the current line as a string
        char lineBuffer[ 2048 ];
        file.getline( lineBuffer, 2048 );
        std::string line( lineBuffer );

        // get the start location
        size_t p = line.find_first_of( ' ' );
        unsigned long start = strtoul( line.substr( 0, p ).c_str(), NULL, 0 );

        line = line.substr( p + 1, line.length() );

        // get the end location
        p = line.find_first_of( ' ' );
        unsigned long end = strtoul( line.substr( 0, p ).c_str(), NULL, 0 );

        // get the file name
        std::string filename = line.substr( p + 1, line.length() );

        // store in maps
        m_libStarts.insert( std::make_pair( filename, start ) );
        m_libEnds.insert( std::make_pair( filename, end ) );
    }
}

void ResourceServer::loadFromLibrary( bool state )
{
    m_loadFromLibrary = state;
}

void ResourceServer::get( const std::string& path, VirtualFile& file )
{
    if ( m_loadFromLibrary )
    {
        readFromLibrary( path, file );
    }
    else
    {
        readFromDisk( path, file );
    }
}

//------------------------------------------------------------------------------
//                            PRIVATE MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void ResourceServer::readFromLibrary( const std::string& path, VirtualFile& file )
{
    // get the start and end locations
    unsigned long start = m_libStarts[ path ];
    unsigned long end   = m_libEnds  [ path ];

    unsigned long size = end - start;

    // open the library file for reading
    FILE* f = fopen( "resources.omi_lib", "rb" );
    if ( f == NULL )
    {
        std::cout << "Resource server failed to open library file" << std::endl;
        // TODO: throw an exception
        return;
    }

    // seek to the start position
    fseek( f, start, SEEK_SET );

    // allocate a char array to store the file data in
    char* buffer = ( char* ) malloc( sizeof( char ) * ( size + 1 ) );
    if ( buffer == NULL )
    {
        std::cout << "Resource server failed to allocate memory for file "
                  << "contents" << std::endl;
        // TODO: throw an exception
        return;
    }

    // copy the file into the buffer
    size_t result = fread( buffer, 1, size, f );
    if ( result != size )
    {
        std::cout << "Resource failed to read library contents into buffer."
                  << std::endl;
        delete buffer;
        // TODO: throw an exception
        return;
    }
    // make sure it's null terminated
    buffer[ size ] = '\0';

    // close the file
    fclose( f );

    // pass on to the virtual file
    file.setData( buffer, size );
}

void ResourceServer::readFromDisk( const std::string& path, VirtualFile& file )
{
    // open the file for reading
    FILE* f = fopen( path.c_str(), "rb" );
    if ( f == NULL )
    {
        std::cout << "Resource server failed to open literal file: "
                  << path << std::endl;
        // TODO: throw an exception
        return;
    }

    // get the size of the file
    fseek( f, 0, SEEK_END );
    long size = ftell( f );
    rewind( f );

    // allocate a char array to store the file data in
    char* buffer = ( char* ) malloc( sizeof( char ) * ( size + 1 ) );
    if ( buffer == NULL )
    {
        std::cout << "Resource server failed to allocate memory for file "
                  << "contents" << std::endl;
        // TODO: throw an exception
        return;
    }

    // copy the file into the buffer
    size_t result = fread( buffer, 1, size, f );
    if ( result != size )
    {
        std::cout << "Resource failed to read file contents into buffer."
                  << std::endl;
        delete buffer;
        // TODO: throw an exception
        return;
    }
    // make sure it's null terminated
    buffer[ size ] = '\0';

    // close the file
    fclose( f );

    // pass on to the virtual file
    file.setData( buffer, size + 1 );
}

} // namespace omi
