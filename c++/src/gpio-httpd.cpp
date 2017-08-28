#include <string>
#include "http-parser.h"
#include "http-server.h"

using namespace std;

/**
 * Prints the usage instructions to the console
 */
void gpio_httpd_usage()
{
  puts("Usage: gpiod [port_number] [document_root]");
}

/**
 * The main entrypoint for gpio-httpd
 * @param  argc Automatically determined argument count
 * @param  argv A pointer to an array of the given arguments
 * @return      The status code of the program.
 */
int main(int argc, char *argv[])
{
  http_srv server;

  unsigned int listen_port = 8080;
  unsigned int max_concurrent_connections = 10;
  string document_root_fp = "/var/www/";

  //Override the default port.
  if ( argc >= 2 )
  {
    try
    {
      listen_port = stoi(argv[1]);
    }
    catch ( invalid_argument e )
    {
      gpio_httpd_usage();
      return 1;
    }
  }

  //Override the root directory.
  if ( argc >= 3 )
  {
    document_root_fp = argv[2];
  }

  server = server_create(listen_port, max_concurrent_connections, document_root_fp);
  server_loop(server);

  return 0;
}
