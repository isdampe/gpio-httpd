#include <iostream>
#include <string>
#include "http-parser.h"

using namespace std;

int main(int argc, char *argv[])
{

  string test_request = "GET / HTTP/1.0\n" \
                        "Host: localhost\n" \
                        "User-agent: Testing!\n\n"; 

  request test = http_parse_request(test_request);

  return 0;
}
