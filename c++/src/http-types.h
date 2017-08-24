#ifndef HTTP_TYPES_
#define HTTP_TYPES_
#include <map>
#include <string>
#include <vector>

using std::string;
using std::map;
using std::vector;

enum request_type
{
  HTTP_UNKNOWN,
  HTTP_GET,
  HTTP_POST
};

enum request_error
{
  NO_ERROR,
  EMPTY_REQUEST,
  BAD_REQUEST,
  UNKNOWN_REQUEST_TYPE,
  INVALID_HTTP_VERSION
};

struct http_request
{
  request_type type;
  request_error error;
  string uri;
  float http_version;
  map<string,string> header_fields;
};

struct http_response
{
  unsigned short status;
  string status_msg;
  string date_time;
  float http_version;
  map<string,string> header_fields;
  unsigned long data_length;
  string data;
};
#endif
