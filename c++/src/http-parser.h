#include <string>
#include <vector>

using namespace std;

enum request_type
{
  HTTP_UNKNOWN,
  HTTP_GET,
  HTTP_POST
};

enum request_error
{
  EMPTY_REQUEST,
  BAD_REQUEST
};

struct request
{
  request_type type;
  request_error error;
  string uri;
  string http_version;
};

request http_parse_request(const string &raw_request);
request_type http_parse_request_type(const vector<string> &lines);
