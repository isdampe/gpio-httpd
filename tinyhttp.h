#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "tinyarray.h"

typedef struct httpd {
  int port;
  char *document_root;
  int sockfd;
  struct sockaddr_in serv_addr;
} httpd;

typedef struct request {
  unsigned char method;
  char *uri;
} request;

#define THTTP_METHOD_UNKNOWN  0
#define THTTP_METHOD_GET      1
#define THTTP_METHOD_POST     2

void tinyhttp_error(const char *msg);
void tinyhttp_setup(httpd *server);
int tinyhttp_serve(httpd *server);
void *tinyhttp_request(int *sockfd);
void tinyhttp_invalid_request(int *sockfd);
void tinyhttp_route_get(int *sockfd);
void tinyhttp_route_post(int *sockfd);
array* tinyhttp_str_split(char *delim, char *buffer);
request tinyhttp_parse_request(char *buffer);
