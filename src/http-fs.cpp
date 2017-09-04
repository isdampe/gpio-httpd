#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

#include "http-status.h"
#include "http-types.h"
#include "http-fs.h"
#include "string_ops.h"

using std::string;
using std::iostream;
using std::fstream;

void http_serve_static_files(const http_request &req, http_response &res, const string &document_root)
{
  struct stat stat_buffer;
  string r_fp;
  ifstream file_data;

  //Build requested file path.
  r_fp = document_root + req.uri;

  //Confirm the file / directory exists.
  if ( stat(r_fp.c_str(), &stat_buffer) == 0 )
  {
    //If it's a directory
    if (stat_buffer.st_mode & S_IFDIR)
    {
      r_fp = r_fp + "/index.html";
    }

  }
  else
  {
    res.status = http_status::NOT_FOUND;
    res.data = "<h1>File Not Found</h1>\n<p>Your request for " + req.uri + " " \
                "could not be found.</p>";
    return;
  }

  //Set data length to file size.
  res.data_length = filesize(r_fp);

  //Set the content-type.
  res.content_type = string_file_extension_to_mime_type(
    string_get_file_extension(r_fp)
  );

  //Let http-server.cpp stream this file.
  res.serve_file = r_fp;

  //Set default status
  res.status = http_status::OK;

}

unsigned long filesize(const string &name)
{
    struct stat stat_buf;
    int rc = stat(name.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
