#include "http-types.h"
#include "string_ops.h"

void http_serve_static_files(const http_request &req, http_response &res)
{
  //Build requested file path.

  //Does requested file path ../../ its way out of document_root?

  //Try to serve the file

  //Determine mime_type with string_file_extension_to_mime_type
  res.status = 200;
  res.status_msg = "OK";
  res.data = "Found";
}
