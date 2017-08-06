#include <string.h>

#include "../src/array.h"
#include "../src/http-parser.h"

int main(int argc, char *argv[])
{

  char test_buffer[] = \
    "GET / HTTP/1.1\n" \
    "Host: localhost\n" \
    "User-agent: Testing Bot\n" \
    "Server: dampe\n\n";

  request new_request;
  new_request = httpd_parse_request(test_buffer);

  return 0;
}
