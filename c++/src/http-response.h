#include "http-types.h"

/**
 * Parses a http_request, takes appropriate action, and generates an
 * appropriate http_response for a HTTP GET request.
 * @param  req The http_request to parse
 * @return     The built http_response
 */
http_response http_create_get_response(const http_request &req);

/**
 * Parses a http_request, takes appropriate action, and generates an
 * appropriate http_response for a HTTP POST request.
 * @param  req The http_request to parse
 * @return     The built http_response
 */
http_response http_create_post_response(const http_request &req);

/**
 * Parses a http_request, takes appropriate action, and generates an
 * appropriate http_response for requests that contain an error.
 * @param  req The http_request to parse
 * @return     The built http_response
 */
http_response http_create_error_response(const http_request &req);

/**
 * Parses a http_response and sets the correct data_length value dependant
 * on the size of the data value.
 * @param res The http_request to set the data_length for
 */
void http_response_set_data_length(http_response &res);
