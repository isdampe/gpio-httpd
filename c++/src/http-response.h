#include <string>
#include "http-types.h"

using namespace std;

http_response http_create_get_response(const http_request &req);
http_response http_create_post_response(const http_request &req);
http_response http_create_error_response(const http_request &req);
void http_response_set_data_length(http_response &res);
