#!/usr/bin/env python

import os

# open the resource header directory
with open( 'resources.omi_h', 'w' ) as lib_header:
    # open the resource library file
    with open( 'resources.omi_lib', 'w' ) as lib_file:
        # find all the files in the resource directory
        for root, _, filenames in os.walk( 'res/' ):
            for filename in filenames:
                filename = os.path.join( root, filename )
                with open( filename ) as f:
                    # write the starting location of the file to the header
                    lib_header.write( str( lib_file.tell() ) + ' ' )
                    # write the file to library
                    lib_file.write( f.read() )
                    # write the ending location of the file to the header
                    lib_header.write( str( lib_file.tell() ) + ' ' )
                    # write the file name to the header
                    lib_header.write( str( filename ) + '\n' )
                    # make sure we end with a new line
                    lib_file.write( '\n' )
