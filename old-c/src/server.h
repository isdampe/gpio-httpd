#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "array.h"

typedef struct httpd {
  int port;
  char *document_root;
  int sockfd;
  struct sockaddr_in serv_addr;
} httpd;

void httpd_error(const char *msg);
void httpd_setup(httpd *server);
int httpd_serve(httpd *server);
void *httpd_request(int *sockfd);
void httpd_invalid_request(int *sockfd);
