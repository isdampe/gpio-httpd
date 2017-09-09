#include <string>

#include "http-status.h"
#include "http-server.h"
#include "http-gpio.h"
#include "http-fs.h"
#include "http-response.h"
#include "map_ops.h"
#include "string_ops.h"

using std::string;

http_response http_create_get_response(const http_request &req, const http_srv &server)
{
  string gpios;
  http_response res = {};
  res.http_version = req.http_version;
  res.date_time = string_get_datetime();
  res.content_type = "text/html; charset=utf-8";

  //Is it a special request?
  gpios = req.uri.substr(0,5);
  if ( gpios == "/gpio" )
  {
    http_build_gpio_get_response(req, res);
  }
  else
  {
    //Static files.
    http_serve_static_files(req, res, server.document_root_dir);
  }

  res.keep_alive = http_should_keep_alive(req);
  res.status_msg = http_get_status_string(res.status);
  http_response_set_data_length(res);

  return res;
}

http_response http_create_post_response(const http_request &req, const http_srv &server)
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
    res.status = http_status::NOT_IMPLEMENTED;
    res.data = "POST is only supported for /gpio requests.";
    http_response_set_data_length(res);
  }

  res.keep_alive = http_should_keep_alive(req);
  res.status_msg = http_get_status_string(res.status);
  http_response_set_data_length(res);

  return res;

}

http_response http_create_error_response(const http_request &req, const http_srv &server)
{
  http_response res = {}; //Ensure the response is empty
  res.http_version = req.http_version;
  res.date_time = string_get_datetime();
  res.content_type = "text/html;";
  res.data = "";
  res.keep_alive = false;
  res.status = req.error;
  res.status_msg = http_get_status_string(res.status);

  return res;
}

void http_response_set_data_length(http_response &res)
{
  if ( res.data != "" )
  {
    res.data_length = (unsigned long)res.data.length();
  }
}

bool http_should_keep_alive(const http_request &req)
{
  //Is there a connection type?
  if ( map_key_exists(req.header_fields, "Connection") )
  {
    if ( req.header_fields.at("Connection") == "keep-alive" )
      return true;
  }

  if ( map_key_exists(req.header_fields, "Proxy-Connection") )
  {
    if ( req.header_fields.at("Proxy-Connection") == "keep-alive" )
      return true;
  }

  return false;
}
