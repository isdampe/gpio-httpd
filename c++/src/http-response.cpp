#include <string>
#include "http-response.h"
#include "string_ops.h"
#include <wiringPi.h>

using namespace std;

http_response http_create_get_response(const http_request &req)
{
  string gpios;
  http_response res = {};
  res.http_version = req.http_version;

  //Is it a special request?
  gpios = req.uri.substr(0,5);
  if ( gpios == "/gpio" )
  {
    printf("SPECIAL GPIO\n\n");
    res.data = "";
  }
  else 
  {
    //Static files.
    res.data = "";
  }

  res.date_time = string_get_datetime();

  res.status = 200;
  res.status_msg = "OK";

  return res;
}

http_response http_create_post_response(const http_request &req)
{
  http_response res = {};
  res.http_version = req.http_version;
  res.data = "";
  res.date_time = string_get_datetime();

  res.status = 200;
  res.status_msg = "OK";

  return res;
}



http_response http_create_error_response(const http_request &req)
{
  http_response res = {}; //Ensure the response is empty
  res.http_version = req.http_version; 
  res.data = "";
  res.date_time = string_get_datetime();
  
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
