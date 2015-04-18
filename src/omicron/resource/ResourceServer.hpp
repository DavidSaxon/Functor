#ifndef OMICRON_RESOURCE_RESOURCESERVER_HPP_
#   define OMICRON_RESOURCE_RESOURCESERVER_HPP_

#define _CRT_SECURE_NO_DEPRECATE

#include <fstream>
#include <iostream>
#include <map>
#include <stdio.h>
#include <stdlib.h>

#include "lib/Utilitron/MacroUtil.hpp"

#include "src/omicron/resource/VirtualFile.hpp"

namespace omi {

class ResourceServer {
private:

    DISALLOW_CONSTRUCTION( ResourceServer );

public:

    //--------------------------------------------------------------------------
    //                          PUBLIC MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** #Hideen
    Initialises the resource server */
    static void init();

    /** Set whether the resource manager will load from the library or from
    disk */
    static void loadFromLibrary( bool state );

    /** @returns the resource file as virtual file */
    static void get( const std::string& path, VirtualFile& file );

private:

    //--------------------------------------------------------------------------
    //                                 VARIABLES
    //--------------------------------------------------------------------------

    // is true to load files from the resource library
    static bool m_loadFromLibrary;

    // a mapping from file names to their start location in the resource lib
    static std::map<std::string, unsigned long> m_libStarts;
    // a mapping from file names to their ending location in the resource lib
    static std::map<std::string, unsigned long> m_libEnds;

    //--------------------------------------------------------------------------
    //                          PRIVATE MEMBER FUNCTIONS
    //--------------------------------------------------------------------------

    /** Reads the given file from the resource library */
    static void readFromLibrary( const std::string& path, VirtualFile& file );

    /** Reads the given file from its literal path */
    static void readFromDisk( const std::string& path, VirtualFile& file );
};

} // namespae omi

#endif
