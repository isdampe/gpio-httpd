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

/**
 * Checks to see whether a given string key exists on a map
 * @param  key_val_map The map of key-value pairs
 * @param  key         The key to check for
 * @return             True if the key exists, otherwise false
 */
bool map_key_exists(const map<string,string> &key_val_map, const string &key);
