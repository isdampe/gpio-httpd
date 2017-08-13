#include <string>
#include <iostream>
#include <string>
#include <vector>

#include "http-parser.h"
#include "string_ops.h"

using namespace std;

request http_parse_request(const string &raw_request)
{
  request result;
  vector<string> lines = string_split_to_vector(raw_request, '\n');

  //Empty request.
  if ( lines.size() < 1 )
  {
    result.error = EMPTY_REQUEST;
    return result;
  }

  //Move the following three things into a procedure "parse http_head"?

  //Determine HTTP request type.
  result.type = http_parse_request_type(lines);
  if ( result.type == HTTP_UNKNOWN )
  {
    result.error = BAD_REQUEST;
    return result;
  }

  //Save URI.
  
  //Check HTTP version.

  return result;

}

request_type http_parse_request_type(const vector<string> &lines)
{
  string http_method_arg;
  request_type result;
  vector<string> args = string_split_to_vector(lines[0], ' ');

  if ( args.size() < 3 )
    return HTTP_UNKNOWN;

  http_method_arg = string_to_upper(args[0]);

  if ( http_method_arg == "GET" )
  {
    return HTTP_GET;
  }
  else if ( http_method_arg == "POST" )
  {
    return HTTP_POST;
  }

  return HTTP_UNKNOWN;

}
