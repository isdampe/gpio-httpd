#include <string>
#include <iostream>
#include <string>
#include <vector>

#include "http-parser.h"
#include "stringvector.h"

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

  //Determine HTTP request type.
  result.type = http_parse_request_type(lines);

  return result;

}

request_type http_parse_request_type(const vector<string> &lines)
{
  request_type result;
  vector<string> args = string_split_to_vector(lines[0], ' ');


  return HTTP_GET;
}
