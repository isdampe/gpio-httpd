#include <fstream>
#include <iostream>
#include <string>
#include "http-types.h"

using std::string;
using std::iostream;
using std::fstream;

/**
 * Parses a HTTP get request and builds an appropriate response, typically
 * serving a static file from the file system.
 * @param req The HTTP request to parse
 * @param res The HTTP response to build
 */
void http_serve_static_files(const http_request &req, http_response &res, const string &document_root);

/**
 * Checks to see whether a specified file exists or not.
 * @param  name The string containing the full file path name
 * @return      True if the file exists, otherwise false.
 */
bool file_exists(const string &name);

/**
 * Calculates the file size in bytes of a given file
 * @param  name The full file path string
 * @return      The size of the file in bytes
 */
unsigned long filesize(const string &name);
