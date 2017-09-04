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
 * Returns the filesize of a file in bytes
 * @param  name The file path name string
 * @return      The file size in bytes
 */
unsigned long filesize(const string &name);
