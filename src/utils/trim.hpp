#include <string>

#ifndef _TRIM_HPP
#define _TRIM_HPP

/**
 * @brief Trim the left end of the input string for whitespaces
 *
 * @param __s A string to be trimmed on the left end
 * @return std::string& Left trimmed string
 */
auto ltrim(std::string& __s) -> std::string&;

/**
 * @brief Trim the right end of the input string for whitespaces
 *
 * @param __s A string to be trimmed on the right end
 * @return std::string& Right trimmed string
 */
auto rtrim(std::string& __s) -> std::string&;

#endif
