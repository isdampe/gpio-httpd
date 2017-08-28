#include "http-types.h"

using std::filesystem;

void http_serve_static_files(const http_request &req, http_response &res)
{
  res.status = 200;
  res.status_msg = "OK";
  res.data = "Found";
}
