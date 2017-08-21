#include <wiringPi.h>
#include "http-types.h"

using namespace std;

void http_build_gpio_get_response(const http_request &req, http_response &res);
void http_build_gpio_post_response(const http_request &req, http_response &res);
