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

/**
 * Returns the extension string of a filename string
 * @param  file_name The filename, i.e. /abc.html
 * @return           The string extension, i.e. html
 */
string string_get_file_extension(const string &file_name);

/**
 * Converts a file extension string to a mime type
 * @param  fe             The file extension string, without the . (i.e. "jpg")
 * @return                The file mime type for use by content-type
 */
string string_file_extension_to_mime_type(string fe);

/**
 * Converts a single char to hex
 * Taken from https://github.com/cmakified/cgicc/find/master
 * License: https://www.gnu.org/software/cgicc/index.html
 * @param  c The single char to convert
 * @return   The hex value
 */
string char_to_hex(char c);

/**
 * Converts a hex value to a char
 * Taken from https://github.com/cmakified/cgicc/find/master
 * License: https://www.gnu.org/software/cgicc/index.html
 * @param  first  The hex value
 * @param  second The second hex value (if any)
 * @return        The char value
 */
char hex_to_char(char first, char second);

/**
 * Converts a string into a URI encoded schema
 * Taken from https://github.com/cmakified/cgicc/find/master
 * License: https://www.gnu.org/software/cgicc/index.html
 * @param  src The string to encode
 * @return     The URI encoded string
 */
string url_encode(const string &src);

/**
 * Decodes a URI encoded string
 * Taken from https://github.com/cmakified/cgicc/find/master
 * License: https://www.gnu.org/software/cgicc/index.html
 * @param  src The URI encoded string
 * @return     The decoded URI string
 */
string url_decode(const string &src);
