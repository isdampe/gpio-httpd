#ifndef HTTP_CACHE_
#define HTTP_CACHE_
#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

typedef map<string,string> http_dynamic_cache;

http_dynamic_cache http_create_dynamic_cache();

#endif
