#include <map>
#include <string>

using std::map;
using std::string;

/**
 * Converts a key-value map pair to a one dimensional JSON string
 * @param  key_val_map The map of key-value pairs
 * @return             The one dimensional JSON string.
 */
string map_to_json_string(map<string,string> key_val_map);
