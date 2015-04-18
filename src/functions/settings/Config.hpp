#ifndef REVERIE_FUNCTIONS_SETTINGS_CONFIG_HPP_
#   define REVERIE_FUNCTIONS_SETTINGS_CONFIG_HPP_

#include <iostream>

namespace settings {

/*****************************************************************************\
| Is used for loading settings from the config file, and handling cases where |
| the config file doesn't exists or is corrupt.                               |
\*****************************************************************************/
namespace config {

//------------------------------------------------------------------------------
//                                   FUNCTIONS
//------------------------------------------------------------------------------

/** Loads and applies the settings from the config file. If the config file is
corrupted or missing then it will be reinstated with the default template */
void applySettingsFromConfig();

/** Parse the value of a config file line into the output string */
void parseConfigLine( const std::string& line, std::string& value );

/** Writes the related settings to the config file */
void writeConfig();

} // namespace config

} // namespace settings

#endif
