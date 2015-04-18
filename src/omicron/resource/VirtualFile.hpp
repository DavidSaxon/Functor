#ifndef OMICRON_RESOURCE_VIRTUALFILE_HPP_
#   define OMICRON_RESOURCE_VIRTUALFILE_HPP_

#include <iostream>
#include <string>

#include "lib/Utilitron/MacroUtil.hpp"

namespace omi {

/**************************************************************************\
| Virtual files are wrappers around the contents of a file that are loaded |
| into memory.                                                             |
\**************************************************************************/
class VirtualFile {
private:

    DISALLOW_COPY_AND_ASSIGN( VirtualFile );

public:

    //--------------------------------------------------------------------------
    //                                CONSTRUCTOR
    //--------------------------------------------------------------------------

    /** Creates a new virtual file that currently holds no data */
    VirtualFile();

    //--------------------------------------------------------------------------
    //                                 DESTURCTOR
    //--------------------------------------------------------------------------

    ~VirtualFile();

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Sets the data of the virtual file and sets the cursor at index 0 */
    void setData( char* data, unsigned long size );

    /** @returns the data of the file */
    char* getData();

    /** @returns the size of the file */
    unsigned long getSize() const;

    /** Resets the cursor to the start of the file */
    void rewind();

    /** @return if there is a another line in the file to read */
    bool hasNextLine();

    /** @return the next line from the file */
    void nextLine( std::string& line );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // the data of the file
    char* m_data;
    // the data size
    unsigned long m_size;
    // the current cursor position
    unsigned m_cursor;

    // is true if there is another line in the file
    bool m_hasNextLine;
};

} // namespace omi

#endif
