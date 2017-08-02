#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
//#include <fcntl.h>
#include <pthread.h>
#include "tinyarray.h"
#include "tinyhttp.h"
#include <stdlib.h>

void tinyhttp_error(const char *msg)
{
  perror(msg);
  exit(1);
}

void tinyhttp_setup(httpd *server) {

  server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->sockfd < 0) 
    tinyhttp_error("ERROR opening socket");

  //Zero the server address memory
  bzero((char *) &server->serv_addr, sizeof(server->serv_addr));

  server->serv_addr.sin_family = AF_INET;
  server->serv_addr.sin_addr.s_addr = INADDR_ANY;
  server->serv_addr.sin_port = htons(server->port);

  //Set non-blocking.
  //This isn't needed, because each event triggered of accept()
  //will launch a thread and then immediately return in the loop.
  //fcntl(server->sockfd, F_SETFL, O_NONBLOCK);

  if (bind(server->sockfd, (struct sockaddr *) &server->serv_addr,
        sizeof(server->serv_addr)) < 0) 
    tinyhttp_error("ERROR on binding");

  listen(server->sockfd, 20);

  printf("Listening on port %i\n", server->port);

}

int tinyhttp_serve(httpd *server) {
  socklen_t clilen;
  struct sockaddr_in cli_addr;
  int newsockfd;
  clilen = sizeof(cli_addr);

  pthread_t thread_id;

  while ( 1 ) {

    //Accept new sockets.
    newsockfd = accept(server->sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) continue;

    //Debug only.
    //tinyhttp_request(newsockfd);

    int thread_result = pthread_create(&thread_id, NULL, tinyhttp_request, (int *)newsockfd);
    if (0 != thread_result) {
      fprintf(stderr, "Error creating pthread");
      continue;
    }
    pthread_detach(thread_id);

  }

  close(server->sockfd);

  return 0;

}

void *tinyhttp_request(int *sockfd) {
  char buffer[256];
  request req;
  int n;

  //Zero the buffer.
  bzero(buffer,256);

  //Try to read the messeg.
  n = read(sockfd,buffer,255);
  if (n < 0) 
    pthread_exit((void *)NULL);

  //Fix this: Keep reading until buffer complete
  req = tinyhttp_parse_request(buffer);
  //printf("Request type: %i\n", req.method);

  switch ( req.method ) {
    case THTTP_METHOD_GET:
      //printf("GET:\n");
      break;
    case THTTP_METHOD_POST:
      //printf("POST:\n");
      break;
    case THTTP_METHOD_UNKNOWN:
    default:
      //printf("Unknown:\n");
      tinyhttp_invalid_request(&sockfd);
      break;
  }
    
  //printf("%s\n", buffer);
  //n = write(sockfd,"I got your message",18);
  //n = write(sockfd, http_method, 1);

  close(sockfd);
  pthread_exit(NULL);

}

request tinyhttp_parse_request(char *buffer) {
  request req;
  char httpd_method[5];
  array *lines;

  //Defaults.
  req.method = THTTP_METHOD_UNKNOWN;

  //Split the buffer into an array of lines.
  lines = tinyhttp_str_split("\n", buffer);

  //Parse the first line, check for HTTP method,
  //request uri, and http version
  
  //Loop through all remaining lines, searching for two \n in a row
  //to indicte the end of the request

  //printf("The size is: %zu\n", lines->size);
  //for ( int i=1; i<(lines->size); i++ ) {
    //printf("CHAR: %s\n", lines->array[i]);
  //}

  //Method type.
  strncpy(httpd_method, buffer, 4);
  if ( strcmp(httpd_method, "GET ") == 0 ) {
    req.method = THTTP_METHOD_GET;
  } else if ( strcmp(httpd_method, "POST") == 0 ) {
    req.method = THTTP_METHOD_POST;
  }

  array_free(lines);

  return req;

}

/**
 * Splits a string by any delimiter as given in delim
 * into an array of strings
 */
array* tinyhttp_str_split(char *delim, char *buffer)
{
  array *result = malloc(sizeof(array));
  char * pch;

  array_init(result);

  pch = strtok (buffer,delim);
  while (pch != NULL)
  {
    
    char *entry = malloc(strlen(pch));
    strncpy(entry, pch, strlen(pch));
    array_append(result, entry);
    //printf ("%s\n",pch);
    pch = strtok (NULL, delim);
  } 

  return result;

}

void tinyhttp_invalid_request(int *sockfd) {

  char *http_headers =
    "HTTP/1.1 400 Bad Request\r\n" \
    "Server: gpio_httpd\r\n" \
    "Content-Type: text/html; charset=iso-8859-1\r\n" \
    "Connection: Closed\r\n\r\n";

  write(*sockfd, http_headers, strlen(http_headers));

}

void tinyhttp_404(int *sockfd) {

  char *http_headers =
    "HTTP/1.1 404 Not Found\r\n" \
    "Server: gpio_httpd\r\n" \
    "Content-Type: text/html; charset=iso-8859-1\r\n" \
    "Connection: Closed\r\n\r\n";

  write(*sockfd, http_headers, strlen(http_headers));

}

void tinyhttp_route_get(int *sockfd) {

}

void tinyhttp_route_post(int *sockfd) {

}
