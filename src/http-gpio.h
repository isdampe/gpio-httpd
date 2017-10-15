#include <map>
#include <vector>
#include "http-types.h"

using std::map;
using std::vector;

/**
 * Parses a HTTP GET request, interacts with GPIO as per the request, builds
 * a response, and then stores it in the provided http_response struct.
 * @param req The http_request to parse
 * @param res The http_response to store the built response in
 */
void http_build_gpio_get_response(const http_request &req, http_response &res, int *gpio_persist);

/**
 * Parses a HTTP POST request, interacts with GPIO as per the request, builds
 * a response, and then stores it in the provided http_response struct.
 * @param req The http_request to parse
 * @param res The http_response to store the built response in
 */
void http_build_gpio_post_response(const http_request &req, http_response &res, int *gpio_persist);

/**
 * Queries a vector of GPIO pins and returns their results in a key-value
 * <string,string> map
 * @param gpio_queries A vector containing a list of GPIO pins to query
 */
map<string,string> http_gpio_query_pins_to_map(const vector<unsigned short> &gpio_queries);

/**
 * Queries a vector of GPIO pins and returns their results in a key-value
 * <string,string> map, from gpio_persist storage.
 * @param gpio_queries    A vector containing a list of GPIO pins to query
 * @param gpio_persist    The gpio_persist pointer
 */
map<string,string> http_gpio_query_pins_to_map(const vector<unsigned short> &gpio_queries, int *gpio_persist);
