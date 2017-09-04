#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "http-parser.h"
#include "string_ops.h"

using std::string;
using std::vector;

http_request http_parse_request(const string &raw_request)
{
  http_request result = {}; //Ensure the struct is empty

  vector<string> lines = string_split_to_vector(raw_request, '\n');

  //Empty request.
  if ( lines.size() < 1 )
  {
    result.error = EMPTY_REQUEST;
    return result;
  }

  //Process the head (i.e. first line)
  http_process_head(result, lines[0]);

  //Process the request head args.
  http_process_header_fields(result, lines);

  return result;

}

void http_process_head(http_request &req, const string &line)
{
  vector<string> args = string_split_to_vector(line, ' ');
  string http_version, http_request_type;

  if ( args.size() < 3 ) {
    req.error = BAD_REQUEST;
    return;
  }

  req.type = http_parse_request_type(args[0]);
  if ( req.type == HTTP_UNKNOWN )
  {
    req.error = UNKNOWN_REQUEST_TYPE;
    return;
  }

  //Save URI.
  req.uri = args[1];

  //Check HTTP version.
  http_version = string_to_upper(args[2]);
  if ( http_version == "HTTP/1.0" )
  {
    req.http_version = 1.0;
  }
  else if ( http_version == "HTTP/1.1" )
  {
    req.http_version = 1.1;
  }
  else
  {
    req.error = INVALID_HTTP_VERSION;
    return;
  }

}

void http_process_header_fields(http_request &req, const vector<string> &lines)
{
  vector<string> line_args;
  int i, max;
  string tmp;

  if ( lines.size() < 2 )
    return;

  max = lines.size();

  for ( i=1; i<max; i++ )
  {
    line_args = string_split_to_vector(lines[i], ':');
    if ( line_args.size() >= 2 )
      req.header_fields[string_to_lower(line_args[0])] = string_trim(line_args[1]);
  }

}


request_type http_parse_request_type(const string &method)
{
  string http_method_arg;

  http_method_arg = string_to_upper(method);

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
