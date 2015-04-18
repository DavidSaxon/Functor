#include "VirtualFile.hpp"

namespace omi {

//------------------------------------------------------------------------------
//                                  CONSTRUCTOR
//------------------------------------------------------------------------------

VirtualFile::VirtualFile()
    :
    m_data       ( NULL ),
    m_size       ( 0 ),
    m_cursor     ( 0 ),
    m_hasNextLine( false)
{
}

//------------------------------------------------------------------------------
//                                   DESTRUCTOR
//------------------------------------------------------------------------------

VirtualFile::~VirtualFile()
{
    // delete the date contained within this file
    delete m_data;
    m_data = NULL;
}

//------------------------------------------------------------------------------
//                            PUBLIC MEMBER FUNCTIONS
//------------------------------------------------------------------------------

void VirtualFile::setData( char* data, unsigned long size )
{
    m_data = data;
    m_size = size;
    m_cursor = 0;

    if ( m_data[0] != '\0' )
    {
        m_hasNextLine = true;
    }
}

char* VirtualFile::getData()
{
    return m_data;
}

unsigned long VirtualFile::getSize() const
{
    return m_size;
}

void VirtualFile::rewind()
{
    m_cursor = 0;
}

bool VirtualFile::hasNextLine()
{
    return m_hasNextLine;
}

void VirtualFile::nextLine( std::string& line )
{
    // store the initial cursor position
    unsigned startCursor = m_cursor;

    // read through the file until we find the next line
    while ( m_data[ m_cursor ] != '\n' &&
            m_data[ m_cursor ] != '\r' &&
            m_data[ m_cursor ] != '\0' )
    {
        ++m_cursor;
    }

    // assign the line data to the string
    if ( m_cursor == startCursor )
    {
        line.assign( "" );
    }
    else
    {
        line.assign( m_data + startCursor, m_cursor - startCursor );
    }

    // fuck you windows
    if ( m_data[ m_cursor ] == '\r' )
    {
        // get past the \n
        m_cursor += 2;
    }
    else if ( m_data[ m_cursor ] == '\n' )
    {
        // go to the next character
        ++m_cursor;
    }

    // check for the end of the file
    if ( m_data[ m_cursor ] == '\0' )
    {
        m_hasNextLine = false;
    }
}

} // namespace omi
