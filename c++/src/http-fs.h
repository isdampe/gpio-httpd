#include "http-types.h"

/**
 * Parses a HTTP get request and builds an appropriate response, typically
 * serving a static file from the file system.
 * @param req The HTTP request to parse
 * @param res The HTTP response to build
 */
void http_serve_static_files(const http_request &req, http_response &res);
