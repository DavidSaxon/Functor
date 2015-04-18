#ifndef UTILITRON_STRINGUTIL_H_
#   define UTILITRON_STRINGUTIL_H_

#include <iostream>
#include <sstream>
#include <vector>

namespace util {

/****************************************\
| Utility functions relating to strings. |
\****************************************/
namespace str {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/** Concatenates an array of strings into one string
@param strings the array of strings to concatenate
@param n the number of strings
@return a new string made from the concatenation */
inline std::string concatenate(std::string strings[], unsigned n) {

    std::stringstream ss;

    // add the strings
    for (unsigned i = 0; i < n; ++i) {

        ss << strings[i];
    }

    return ss.str();
}

/** Concatenates the second string in front of the first string
@param a the string to be extended
@param b the string to concatenate on to the front of the other string */
inline void concatenateFront(std::string& a, const std::string& b) {

    // create a new string stream
    std::stringstream ss;
    // add the strings to it
    ss << b << a;

    // set the new string
    a = ss.str();
}

/** Concatenates the second string on to the end of the first string
@param a the string to be extended
@param b the string to concatenate on to the end of the other string* */
inline void concatenateBack(std::string& a, const std::string& b) {

    // create a new string stream
    std::stringstream ss;
    // add the strings to it
    ss << a << b;

    // set the new string
    a = ss.str();
}

/** Checks if a given string begins with a string
@param a the string to check if it begins with the other string
@param b the suffix to check for in the first string
@return if the first string begins with the second string */
inline bool beginsWith(const std::string& a, const std::string& b) {

    return a.compare(0, b.length(), b) == 0;
}

/** Checks if a given string with another string
@param a the string to check if it ends with the other string
@param b the string to check if the string ends with
@return if the first string ends with the second string */
inline bool endsWith( const std::string& a, const std::string& b )
{
    if ( a.length() > b.length() )
    {
        return a.compare( a.length() - b.length(), b.length(), b ) == 0;
    }
    else
    {
        return false;
    }
}

/** @return if the given string is an integer */
inline bool isInt( const std::string& s )
{
    // TODO: trim string first

    // iterate over each character and check if it's a digit, except for the
    // first character which may be '-'
    for ( unsigned i = 0; i < s.length(); ++i )
    {
        if ( i == 0 && s.at( i ) !=  '-' && !isdigit( s.at( i ) ) )
        {
            return false;
        }
        if ( i != 0 && !isdigit( s.at( i ) ) )
        {
            return false;
        }
    }

    return true;
}

/** @return if the given string is an unsigned integer */
inline bool isUInt( const std::string& s )
{
    // TODO: trim string first

    // iterate over each character and check that it is a digit
    for ( unsigned i = 0; i < s.length(); ++i )
    {
        if ( !isdigit( s.at( i ) ) )
        {
            return false;
        }
    }

    return true;
}

/** @return true if the given string is a floating point number */
inline bool isFloat( const std::string& s )
{
    // TODO: trim string first

    bool pointFound = false;
    // iterate over each character and check
    for ( unsigned i = 0; i < s.length(); ++i )
    {
        if ( !isdigit( s.at( i ) ) )
        {
            if ( i == 0 && s.at( i ) == '-' )
            {
                continue;
            }
            if ( s.at( i ) == '.' && !pointFound )
            {
                pointFound = true;
                continue;
            }

            return false;
        }
    }

    return true;
}

/** Splits a string into a vector by a given delimiter
@param str the string to split
@param delimiter the delimiter to split the string by
@oaram elements the vector to store the split elements in*/
inline std::vector<std::string>& split(
        const std::string&              str,
              char                      delimiter,
              std::vector<std::string>& elements) {

    std::stringstream ss(str);
    std::string item;

    // iterate over the elements split by the delimiter
    while (std::getline(ss, item, delimiter)) {

        if (item.length() > 0) {

            elements.push_back(item);
        }
    }

    return elements;
}

/** Generates a string containing a string repeated a given amount of times
@param str the string to repeat
@param n the number of times to repeat the character
@return the generated string */
inline std::string generateRepeat(const std::string& str, unsigned n) {

    // create a new string stream
    std::stringstream ss;
    for (unsigned i = 0; i < n; ++i) {

        ss << str;
    }

    return ss.str();
}

//TODO: centre a string on multiple lines
/** Centres a string so that it occupies a given number of characters. If the
string is longer than the given number of characters it is split into
multiple lines
#WARNING This will not trim white-space from the initial string so any
proceeding or trailing white-space will be considered part of the string
to centre.
#WARNING If the string initially occupies multiple lines each line of the
string will be centered to occupy the given number of characters.
@param str the string to centre
@param charNum the number of characters the string should occupy
@return the number of lines the string now occupies */
inline unsigned centre(std::string& str, unsigned charNum) {

    //TODO: check for new lines (windows too)

    // check the length of the string
    if (str.length() < charNum) {

        // find the number of characters to add
        int addLength = charNum - str.length();

        // generate the spaces to add
        std::string whiteSpace = generateRepeat(" ", addLength / 2);

        // add the white space to the string
        concatenateFront(str, whiteSpace);
        concatenateBack(str, whiteSpace);

        // if odd add an extra space to the end
        if (addLength % 2) {

            concatenateBack(str, " ");
        }

        return 1;
    }
    else if (str.length() > charNum) {

        //TODO:
    }

    // if the string is equal to the number of characters
    return 1;
}

} // namespace str

} // namespace util

#endif
