#include <map>
#include <string>
#include <stdlib.h>

using std::map;
using std::string;
using std::iterator;

string map_to_json_string(map<string,string> key_val_map)
{
  string result = "";
  map<string,string>::iterator it;

printf("Testing");
  for ( it = key_val_map.begin(); it != key_val_map.end(); ++it )
  {
    printf("Key: %s, Value: %s\n", it->first.c_str(), it->second.c_str());
  }

  return result;
}
