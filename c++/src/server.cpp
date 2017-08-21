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
#include <thread>
#include <iostream>

#include "http-parser.h"
#include "http-response.h"
#include "server.h"
#include "string_ops.h"

#define TCP_BUFFER_SIZE 1024

//2MB.
#define HTTP_MAX_REQUEST_SIZE 2097152

const std::string SERVER_NAME = "gpiohttpd";
const std::string SERVER_VERSION = "0.1.0";
const std::string SERVER_SIGNATURE = SERVER_NAME + "/" + SERVER_VERSION;

http_srv server_create(const unsigned short port, const int max_queue)
{
  http_srv server;

  //Create the socket.
  server.sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server.sock_fd < 0) 
    printf("Error opening socket!\n"); 

  //Set socket options
  int optval = 1;
  if ( setsockopt(server.sock_fd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
                  sizeof(int)) == -1 )
  {
    printf("Error setting socket option!\n");
  }

  bzero((char *) &server.addr, sizeof(server.addr));
  server.addr.sin_family = AF_INET;

  //Automatically determine IP address
  server.addr.sin_addr.s_addr = htonl(INADDR_ANY);

  //Set listen port
  server.addr.sin_port = htons(port);

  //Bind to socket.
  if (::bind(server.sock_fd, (struct sockaddr *) &server.addr, 
	   sizeof(server.addr)) < 0) 
  {
    printf("Error when binding\n");
    close(server.sock_fd);
  }

  //Mark the socket as ready to listen.
  if (listen(server.sock_fd, max_queue) < 0) 
  {
    printf("Error setting socket to listen\n");
    close(server.sock_fd);
  }

  return server;

}

void server_loop(http_srv &server)
{
  struct sockaddr_in client_addr;
  int client_fd, n;
  socklen_t client_len;
  char buf[TCP_BUFFER_SIZE];

  while (1) {

    //Wait for a connection.
    client_fd = accept(server.sock_fd, (struct sockaddr *) &client_addr, &client_len);
    if (client_fd < 0) 
      printf("Error when accepting socket\n");

    std::thread req(server_handle_request, client_fd);
    req.detach();

  }

}

void server_handle_request(const int client_fd)
{
  http_client client;
  char buf[TCP_BUFFER_SIZE];
  unsigned int r_bytes_read = 0;
  std::string buffer, response;
  size_t eor_search;
  http_request http_req;
  http_response http_res;

  client.client_fd = client_fd;

  //Clear the buffer data.
  bzero(buf, TCP_BUFFER_SIZE);

  //Read the buffer data.
  while (1)
  {
    client.n = read(client.client_fd, buf, TCP_BUFFER_SIZE);
    if (client.n <= 0) 
    {
      //printf("ERROR reading from socket\n");
      client.error = CLIENT_UNKNOWN_ERROR;
      break;
    }

    //Increment the number of bytes read.
    r_bytes_read += strlen(buf);

    //Add the read-in buffer to the string buffer.
    buffer += buf;

    //If we have been waiting too long...

    //Request size too big. Drop.
    if ( r_bytes_read >= HTTP_MAX_REQUEST_SIZE )
    {
      client.error = CLIENT_REQUEST_TOO_LARGE;
      break;
    }

    //If \r\n exists, end of request.
    eor_search = buffer.rfind("\r\n\r\n");
    if ( eor_search!=std::string::npos )
    {
      break;
    }

    //Reclear the buffer.
    bzero(buf, TCP_BUFFER_SIZE);

  }
 
  http_req = http_parse_request(buffer);

  if ( (int)http_req.error > 0 )
  {
    //Handle error respone.
    http_res = http_create_error_response(http_req);
  }
  else {
  
    //Route the request.
    switch(http_req.type)
    {
      case request_type::HTTP_GET:
        http_res = http_create_get_response(http_req);
        break;
      case request_type::HTTP_POST:
        http_res = http_create_post_response(http_req);
        break;
      default:
        http_res = http_create_error_response(http_req);
        break;
    }
  
  }

  /*
  printf("Type: %i\n", (int)http_req.type);
  printf("URI: %s\n", http_req.uri.c_str());
  printf("HTTP Version: %f\n", http_req.http_version);
  printf("User agent: %s\n", http_req.header_fields["user-agent"].c_str());
  printf("Host: %s\n", http_req.header_fields["host"].c_str());
  */

  server_reply(client, http_res);

  //Should I close, i.e. keep open?
  close(client.client_fd);

}

void server_reply(const http_client &client, const http_response &response)
{
  string str_res;
  int n;

  //Head.
  str_res = "HTTP/1.1 " + to_string(response.status) + " " + \
             response.status_msg + "\r\n";

  //Date.
  str_res += "Date: " + response.date_time + "\r\n";
  
  //Server.
  str_res += "Server: " + SERVER_SIGNATURE + "\r\n";

  //Various other headers.

  //Data.
  if ( response.data_length > 0 )
  {
    str_res += "Content-Length: " + to_string(response.data_length) + "\r\n\r\n";
    str_res += response.data + "\r\n";
  }
  
  //Send it.
  write(client.client_fd, str_res.c_str(), strlen(str_res.c_str()));
  if (n < 0)
    printf("ERROR writing to socket\n");

  //If not keep open
  //close(client.client_fd);

}
