typedef struct request {
  unsigned char method;
  char *uri;
} request;

#define THTTP_METHOD_UNKNOWN  0
#define THTTP_METHOD_GET      1
#define THTTP_METHOD_POST     2

array* httpd_str_split(char *delim, char *buffer);
request httpd_parse_request(char *buffer);
