#include <string>
#include <vector>

#include "http-types.h"

using std::string;
using std::vector;

/**
 * Accepts a raw string HTTP request, parses it, and returns the pre-built
 * http_request struct.
 * @param  raw_request The string containing the HTTP request body
 * @return             The pre-built http_request struct
 */
http_request http_parse_request(const string &raw_request);

/**
 * Parses a string and returns the appropriate request_type enum.
 * @param  method The string to parse, i.e. "GET" or "POST"
 * @return        The appropriate request_type enumeration
 */
request_type http_parse_request_type(const string &method);

/**
 * Processes the head line of a http request string, and builds appropriate
 * data on the provided http_request struct. Checks HTTP versions, sets the
 * request URI, and sets r.error where appropraite.
 * @param r    The http_request to build
 * @param line The head line of a http request string
 */
void http_process_head(http_request &req, const string &line);

/**
 * Processes all headers fields in a http request string, and stores them in
 * the provided http_request struct's header_fields vector as key value pairs.
 * @param r     The http_request to build
 * @param lines The whole http request string
 */
void http_process_header_fields(http_request &req, const vector<string> &lines);
