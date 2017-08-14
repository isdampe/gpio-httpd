#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>

#include "http-parser.h"
#include "string_ops.h"

using namespace std;

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

void http_process_head(http_request &r, const string &line)
{
  vector<string> args = string_split_to_vector(line, ' ');
  string http_version;

  if ( args.size() < 3 ) {
    r.error = BAD_REQUEST;
    return;
  }

  r.type = http_parse_request_type(args);
  if ( r.type == HTTP_UNKNOWN )
  {
    r.error = UNKNOWN_REQUEST_TYPE;
    return;
  }

  //Save URI.
  r.uri = args[1];
  
  //Check HTTP version.
  http_version = string_to_upper(args[2]);
  if ( http_version == "HTTP/1.0" )
  {
    r.http_version = 1.0;
  }
  else if ( http_version == "HTTP/1.1" )
  {
    r.http_version = 1.1;
  } 
  else 
  {
    r.error = INVALID_HTTP_VERSION;
    return;
  }

}

void http_process_header_fields(http_request &r, const vector<string> &lines)
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
    r.header_fields[string_to_lower(line_args[0])] = string_trim(line_args[1]);
  }

}

request_type http_parse_request_type(const vector<string> &args)
{
  string http_method_arg;
  request_type result;

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
