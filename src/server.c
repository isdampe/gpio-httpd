#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdlib.h>

#include "array.h"
#include "http-parser.h"
#include "server.h"

void httpd_error(const char *msg)
{
  perror(msg);
  exit(1);
}

void httpd_setup(httpd *server) {

  server->sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (server->sockfd < 0) 
    httpd_error("ERROR opening socket");

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
    httpd_error("ERROR on binding");

  listen(server->sockfd, 20);

  printf("Listening on port %i\n", server->port);

}

int httpd_serve(httpd *server) {
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
    //httpd_request(newsockfd);

    int thread_result = pthread_create(&thread_id, NULL, httpd_request, (int *)newsockfd);
    if (0 != thread_result) {
      fprintf(stderr, "Error creating pthread");
      continue;
    }
    pthread_detach(thread_id);

  }

  close(server->sockfd);

  return 0;

}

void *httpd_request(int *sockfd) {
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
  req = httpd_parse_request(buffer);
  //printf("Request type: %i\n", req.method);

  switch ( req.method ) {
    case HTTPD_MTHD_GET:
      //printf("GET:\n");
      break;
    case HTTPD_MTHD_POST:
      //printf("POST:\n");
      break;
    case HTTPD_MTHD_GET_GPIO:
      //printf("GETTT GPIO:\n");
      break;
    case HTTPD_MTHD_UNKNOWN:
    default:
      //printf("Unknown:\n");
      httpd_invalid_request(&sockfd);
      break;
  }
    
  //printf("%s\n", buffer);
  //n = write(sockfd,"I got your message",18);
  //n = write(sockfd, http_method, 1);

  close(sockfd);
  pthread_exit(NULL);

}

void httpd_invalid_request(int *sockfd) {

  char *http_headers =
    "HTTP/1.1 400 Bad Request\r\n" \
    "Server: gpio_httpd\r\n" \
    "Content-Type: text/html; charset=iso-8859-1\r\n" \
    "Connection: Closed\r\n\r\n";

  write(*sockfd, http_headers, strlen(http_headers));

}

void httpd_404(int *sockfd) {

  char *http_headers =
    "HTTP/1.1 404 Not Found\r\n" \
    "Server: gpio_httpd\r\n" \
    "Content-Type: text/html; charset=iso-8859-1\r\n" \
    "Connection: Closed\r\n\r\n";

  write(*sockfd, http_headers, strlen(http_headers));

}

void httpd_route_get(int *sockfd) {

}

void httpd_route_post(int *sockfd) {

}
