#ifndef UTILITRON_FILEUTIL_H_
#   define UTILITRON_FILEUTIL_H_

#include <fstream>

namespace util {

/**************************************************\
| Utilities relating to files and the file system. |
\**************************************************/
namespace file {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/** Reads a file into a string
@param filePath the path of the file to read
@param str the string to read the contents into
@return the string contains the file contents */
inline std::string fileToString(
    const std::string& filePath,
          std::string& str) {

    std::ifstream in(filePath.c_str(), std::ios::in | std::ios::binary);

    if (in) {

        in.seekg(0, std::ios::end);
        str.resize(static_cast<unsigned>(in.tellg()));
        in.seekg(0, std::ios::beg);
        in.read(&str[0], str.size());
        in.close();
    }

    return str;
}

} // namespace file

} // namespace util

#endif