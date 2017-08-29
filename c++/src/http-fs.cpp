#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "http-types.h"
#include "http-fs.h"
#include "string_ops.h"

using std::string;
using std::iostream;
using std::fstream;

void http_serve_static_files(const http_request &req, http_response &res, const string &document_root)
{
  string r_fp;
  ifstream file_data;

  //Build requested file path.
  r_fp = document_root + ( req.uri == "/" ? "/index.html" : req.uri );

  //Does requested file path ../../ its way out of document_root?
  if (! file_exists(r_fp) )
  {
    res.status = 404;
    res.status_msg = "Not Found";
    res.data = "<h1>File Not Found</h1>\n<p>Your request for " + req.uri + " " \
                "could not be found.</p>";
    return;
  }

  //Try to serve the file


  //Determine mime_type with string_file_extension_to_mime_type
  res.status = 200;
  res.status_msg = "OK";
  res.data = r_fp;
}

bool file_exists(const string &name)
{
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}
