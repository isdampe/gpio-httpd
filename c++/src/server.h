#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

enum http_client_error
{
  CLIENT_UNKNOWN_ERROR,
  CLIENT_BAD_REQUEST,
  CLIENT_REQUEST_TOO_LARGE,
  CLIENT_TIMEOUT
};

struct http_srv 
{
  int sock_fd;
  struct sockaddr_in addr;
};

struct http_client
{
  int client_fd;
  int n;
  struct sockaddr_in addr;
  http_client_error error;
};


http_srv server_create(const unsigned short port, const int max_queue);
void server_loop(http_srv &server);
void server_handle_request(const int client_fd);
void server_reply(const http_client &client, const http_response &response);
