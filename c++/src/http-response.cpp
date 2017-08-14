#include <string>
#include "http-response.h"

using namespace std;

http_response http_create_response(const http_request &req)
{
  http_response res; 

  return res;
}

http_response http_create_error_response(const http_request &req)
{
  http_response res = {}; //Ensure the response is empty
  res.http_version = req.http_version; 
  res.data = "";
  
  switch( req.error )
  {
    case EMPTY_REQUEST:
      res.status = 400;
      res.status_msg = "Bad Request";
      break;
    case BAD_REQUEST:
      res.status = 400;
      res.status_msg = "Bad Request";
      break;
    case INVALID_HTTP_VERSION:
      res.status = 505;
      res.status_msg = "HTTP Version Not Supported";
      break;
    case UNKNOWN_REQUEST_TYPE:
      res.status = 501;
      res.status_msg = "Not Implemented";
      break;
    default:
      res.status = 500;
      res.status_msg = "Internal Server Error";
      break;
  }

  return res;
}
