#include <string.h>
#include <stdio.h>

#include "../src/array.h"
#include "../src/http-parser.h"

int main(int argc, char *argv[])
{

  char test_buffer[] = \
    "GET /gpio/1 HTTP/1.1\n" \
    "Host: localhost\n" \
    "User-agent: Testing Bot\n" \
    "Server: dampe\n\n";

  request new_request;
  new_request = httpd_parse_request(test_buffer);

  switch ( new_request.method ) {
    case HTTPD_MTHD_GET:
      puts("TYPE: GET");
      break;
    case HTTPD_MTHD_POST:
      puts("TYPE: POST");
      break;
    case HTTPD_MTHD_GET_GPIO:
      puts("TYPE: Special case GET (GPIO)");
      break;
  }

  printf("Request URI: %s\n", new_request.uri);

  return 0;
}
