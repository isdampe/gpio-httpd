#include <string>
#include <arpa/inet.h>
#include "http-types.h"

using std::string;

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
  string document_root_dir;
};

struct http_client
{
  int client_fd;
  int n;
  struct sockaddr_in addr;
  http_client_error error;
};

/**
 * Creates a http_srv instance, creates a TCP port, sets its options, binds to
 * it, and attempts to listen on it. Sets appropriate values in http_srv.
 * @param  port             The TCP port number to listen on
 * @param  max_queue        The total number of connections allowed in the queue
 * @param  document_root_fp The document root directory path
 * @return                  The built http_srv instance
 */
http_srv server_create(const unsigned int port, const unsigned int max_queue, string document_root_fp);

/**
 * The main loop for processing a http_srv instance. Continuously accepts
 * TCP socket connections and launches a new thread to deal with each
 * connection.
 * @param server The http_srv instance to process.
 */
void server_loop(http_srv &server);

/**
 * Handles a socket connection (launched in a new thread)
 * Creates a buffer, loops around listening for data from the socket. Watches
 * and detects the end of a HTTP request. Routes the requests appropriately.
 * @param client_fd The client socket descriptor identifier
 */
void server_handle_request(const http_srv &server, const int client_fd);

/**
 * Generates HTTP response HEAD string
 * @param response The http_response to parse and build
 * @return         The HTTP head string
 */
string server_generate_head_string(const http_response &response);

/**
 * Uses a prebuilt http_response to reply to a client
 * @param client   The http_client to reply to
 * @param response The http_response to reply with
 */
void server_reply(const http_client &client, const http_response &response);

/**
 * Uses a prebuilt http_response to stream a file to a client
 * @param client   The http_client to stream the data to
 * @param response The http_response to reply with
 */
void server_stream_file(const http_client &client, http_response &response);
