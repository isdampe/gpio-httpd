#include <stdio.h>
#include <stdlib.h>
#include "server.h"

void httpd_usage()
{
  fprintf(stderr, "Usage: httpd listen_port [document_root]\n");
}

int main(int argc, char *argv[])
{
  char* httpd_document_root = "/var/www";

  httpd server;
  server.document_root = httpd_document_root;

  if (argc < 2) {
    httpd_usage();
    return 1;
  }

  server.port = atoi(argv[1]);
  server.document_root = (argc >= 3) ? argv[2] : httpd_document_root;

  printf("Going to listen on port %i\n", server.port);
  printf("Server directory %s\n", server.document_root);

  httpd_setup(&server);
  httpd_serve(&server);

  return 0; 
}
