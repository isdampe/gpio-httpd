#include <map>
#include <string>
#include <stdlib.h>

using std::map;
using std::string;
using std::iterator;

string map_to_json_string(map<string,string> key_val_map)
{
  string result = "{";
  map<string,string>::iterator it;

  for ( it = key_val_map.begin(); it != key_val_map.end(); ++it )
  {
    result += "\"" + it->first + "\":"; //"key":
    result += "\"" + it->second + "\",";//"value",
  }

  //Strip remaining comma
  if ( result.substr(result.length() -1, 1) == "," )
    result = result.substr(0, result.length() -1);

  result += "}";

  return result;
}

bool map_key_exists(const map<string,string> &key_val_map, const string &key)
{
  if ( key_val_map.find(key) == key_val_map.end() )
    return false;

  return true;
}
