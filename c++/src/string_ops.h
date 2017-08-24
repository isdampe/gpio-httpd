#include <string>
#include <vector>

using namespace std;

/**
 * Splits a string by single char into a std::vector
 * @param  s     The subject string
 * @param  delim The single char delimeter
 * @return       The vector of the split results
 */
vector<string> string_split_to_vector(const string &s, char delim);

/**
 * Converts a string to lowercase
 * @param  s The subject string
 * @return   The string converted to lowercase
 */
string string_to_lower(const string &s);

/**
 * Converts a string to uppercase
 * @param  s The subject string
 * @return   The string converted to uppercase
 */
string string_to_upper(const string &s);

/**
 * Removes the whitespace present on the left side of a string
 * @param  s          The subject string
 * @param  whitespace The string "needle" for whitespace search
 * @return            The stripped string
 */
string string_trim(const string &s, const string &whitespace = " \t");

/**
 * Returns a string containing the current date and time in the standard
 * format for HTTP usage
 * @return The string containing the current date and time
 */
string string_get_datetime();
