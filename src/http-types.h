#ifndef HTTP_TYPES_
#define HTTP_TYPES_
#include <map>
#include <string>
#include <vector>
#include "http-status.h"

using std::string;
using std::map;
using std::vector;

enum request_type
{
  HTTP_UNKNOWN,
  HTTP_GET,
  HTTP_POST
};

struct http_request
{
  request_type type;
  http_status error;
  string uri;
  string get_args;
  float http_version;
  map<string,string> header_fields;
};

struct http_response
{
  http_status status;
  string status_msg;
  string date_time;
  float http_version;
  map<string,string> header_fields;
  string content_type;
  string serve_file;
  unsigned long data_length;
  string data;
};
#endif
