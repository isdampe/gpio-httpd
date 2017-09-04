#include <string>
#include "http-status.h"

using std::string;

string http_get_status_string(const http_status &status)
{
    switch( status )
    {
      case http_status::OK:
        return "OK";
      break;
      case http_status::CREATED:
        return "Created";
      break;
      case http_status::ACCEPTED:
        return "Accepted";
      break;
      case http_status::NON_AUTHORITATIVE_INFO:
        return "Non-authoritative Information";
      break;
      case http_status::NO_CONTENT:
        return "No Content";
      break;
      case http_status::MULTIPLE_CHOICES:
        return "Multiple Choices";
      break;
      case http_status::MOVED_PERMANENTLY:
        return "Moved Permanently";
      break;
      case http_status::FOUND:
        return "Found";
      break;
      case http_status::NOT_MODIFIED:
        return "Not Modified";
      break;
      case http_status::TEMPORARY_REDIRECT:
        return "Temporary Redirect";
      break;
      case http_status::PERMANENT_REDIRECT:
        return "Permanent Redirect";
      break;
      case http_status::BAD_REQUEST:
        return "Bad Request";
      break;
      case http_status::UNAUTHORIZED:
        return "Unauthorized";
      break;
      case http_status::FORBIDDEN:
        return "Forbidden";
      break;
      case http_status::NOT_FOUND:
        return "Not Found";
      break;
      case http_status::METHOD_NOT_ALLOWED:
        return "Method Not Allowed";
      break;
      case http_status::REQUEST_URI_TOO_LONG:
        return "Request-URI Too Long";
      break;
      case http_status::INTERNAL_SERVER_ERROR:
        return "Internal Server Error";
      break;
      case http_status::NOT_IMPLEMENTED:
        return "Not Implemented";
      break;
      case http_status::BAD_GATEWAY:
        return "Bad Gateway";
      break;
      case http_status::SERVICE_UNAVAILABLE:
        return "Service Unavailable";
      break;
      case http_status::HTTP_VERSION_NOT_SUPPORTED:
        return "HTTP Version Not Supported";
      break;
      default:
        return "Not Implemented";
      break;
    }
}
