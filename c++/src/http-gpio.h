#include <wiringPi.h>
#include "http-types.h"

/**
 * Parses a HTTP GET request, interacts with GPIO as per the request, builds
 * a response, and then stores it in the provided http_response struct.
 * @param req The http_request to parse
 * @param res The http_response to store the built response in
 */
void http_build_gpio_get_response(const http_request &req, http_response &res);

/**
 * Parses a HTTP POST request, interacts with GPIO as per the request, builds
 * a response, and then stores it in the provided http_response struct.
 * @param req The http_request to parse
 * @param res The http_response to store the built response in
 */
void http_build_gpio_post_response(const http_request &req, http_response &res);
