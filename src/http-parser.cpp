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
  http_request req = {}; //Ensure the struct is empty

  vector<string> lines = string_split_to_vector(raw_request, '\n');

  //Empty request.
  if ( lines.size() < 1 )
  {
    req.error = http_status::BAD_REQUEST;
    return req;
  }

  //Process the head (i.e. first line)
  http_process_head(req, lines[0]);

  //Process the request head args.
  http_process_header_fields(req, lines);

  return req;

}

void http_process_head(http_request &req, const string &line)
{
  vector<string> args = string_split_to_vector(line, ' ');
  string http_version, http_request_type;

  if ( args.size() < 3 ) {
    req.error = http_status::BAD_REQUEST;
    return;
  }

  req.type = http_parse_request_type(args[0]);
  if ( req.type == HTTP_UNKNOWN )
  {
    req.error = http_status::NOT_IMPLEMENTED;
    return;
  }

  //Save URI.
  req.uri = url_decode(args[1]);

  //If there are get arguments, separate them.
  size_t strpos = req.uri.find("?");
  if ( strpos != string::npos )
  {
    vector<string> uri_split = string_split_to_vector(req.uri, '?');
    req.uri = uri_split[0];
    req.get_args = uri_split[1];
  }

  //Prevent directory traversal
  req.uri = string_replace_all(req.uri, "../", "");

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
    req.error = http_status::HTTP_VERSION_NOT_SUPPORTED;
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
      req.header_fields[line_args[0]] = string_trim(line_args[1]);
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
