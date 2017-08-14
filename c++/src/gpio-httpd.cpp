#include <iostream>
#include <stdio.h>
#include <string>
#include "http-parser.h"
#include "server.h"

using namespace std;

int main(int argc, char *argv[])
{

  http_srv server;

  server = server_create(8001, 10);
  server_loop(server);


  /**
  string test_request = "GET /abc/def HTTP/1.1\n" \
                        "Host: localhost\n" \
                        "User-agent: Testing!\n\n"; 

  request test = http_parse_request(test_request);
  printf("Type: %i\n", (int)test.type);
  printf("URI: %s\n", test.uri.c_str());
  printf("HTTP Version: %f\n", test.http_version);
  printf("User agent: %s\n", test.header_fields["user-agent"].c_str());
  printf("Host: %s\n", test.header_fields["host"].c_str());
  */

  return 0;
}
