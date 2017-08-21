#include <map>
#include <string>
#include <vector>

#include "http-types.h"

using namespace std;

http_request http_parse_request(const string &raw_request);
request_type http_parse_request_type(const vector<string> &args);
void http_process_head(http_request &r, const string &line);
void http_process_header_fields(http_request &r, const vector<string> &lines);
