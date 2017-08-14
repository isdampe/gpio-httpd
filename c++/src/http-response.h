#include <string>
#include "http-types.h"

using namespace std;

http_response http_create_response(const http_request &req);
http_response http_create_error_response(const http_request &req);
