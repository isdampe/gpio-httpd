#include <string>
#include "http-gpio.h"
#include "http-fs.h"
#include "http-response.h"
#include "string_ops.h"

using std::string;

http_response http_create_get_response(const http_request &req, const string &document_root)
{
  string gpios;
  http_response res = {};
  res.http_version = req.http_version;
  res.date_time = string_get_datetime();
  res.content_type = "text/html;";

  //Is it a special request?
  gpios = req.uri.substr(0,5);
  if ( gpios == "/gpio" )
  {
    http_build_gpio_get_response(req, res);
  }
  else
  {
    //Static files.
    http_serve_static_files(req, res);
  }

  http_response_set_data_length(res);

  return res;
}

http_response http_create_post_response(const http_request &req, const string &document_root)
{
  string gpios;
  http_response res = {};
  res.http_version = req.http_version;
  res.date_time = string_get_datetime();
  res.content_type = "text/html;";
  res.data = "";

  //Is it a special request?
  gpios = req.uri.substr(0,5);
  if ( gpios == "/gpio" )
  {
    http_build_gpio_post_response(req, res);
  }
  else
  {
    res.status = 501;
    res.status_msg = "Not Implemented";
    res.data = "POST is only supported for /gpio requests.";
    http_response_set_data_length(res);
  }

  http_response_set_data_length(res);

  return res;

}

http_response http_create_error_response(const http_request &req)
{
  http_response res = {}; //Ensure the response is empty
  res.http_version = req.http_version;
  res.date_time = string_get_datetime();
  res.content_type = "text/html;";
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

void http_response_set_data_length(http_response &res)
{
  if ( res.data != "" )
  {
    res.data_length = (unsigned long)res.data.length();
  }
}
