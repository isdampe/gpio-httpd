#include <string>
#include "http-types.h"
#include "string_ops.h"
#include <wiringPi.h>

using std::string;

void http_build_gpio_get_response(const http_request &req, http_response &res)
{
  int gpio_pin, gpio_state;
  wiringPiSetup();

  vector<string> uri_components = string_split_to_vector(req.uri, '/');
  if ( uri_components.size() != 2 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    res.data = "Missing pin.";
    return;
  }

  //Convert the chosen pin to an integer.
  gpio_pin = stoi(uri_components[1].c_str(), nullptr);

  //Check to see if the pin number is valid as a digital pin.
  if ( gpio_pin < 0 || gpio_pin > 31 )
  {
    res.status = 400;
    res.data = "The requested pin is out of range [0-31].";
    return;
  }

  //Set the pin mode to input for reading.
  pinMode(gpio_pin, INPUT);

  //Read the value of the pin.
  gpio_state = digitalRead(gpio_pin);

  res.status = 200;
  res.status_msg = "OK";
  res.data = to_string(gpio_state);

}

void http_build_gpio_post_response(const http_request &req, http_response &res)
{
  int gpio_pin, gpio_state;
  wiringPiSetup();

  vector<string> uri_components = string_split_to_vector(req.uri, '/');
  if ( uri_components.size() != 3 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    res.data = "Missing pin or pin status.";
    return;
  }

  //Convert the chosen pin to an integer.
  gpio_pin = stoi(uri_components[1].c_str(), nullptr);

  //Check to see if the pin number is valid as a digital pin.
  if ( gpio_pin < 0 || gpio_pin > 31 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    res.data = "The requested pin is out of range [0-31].";
    return;
  }

  //Convert the state request to an integer.
  gpio_state = stoi(uri_components[2].c_str(), nullptr);
  if ( gpio_state < 0 || gpio_state > 1 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    res.data = "The requested pin status must either be 0 or 1.";
  }

  //Set the pin mode to input for reading.
  pinMode(gpio_pin, OUTPUT);

  //Write to the pin.
  digitalWrite(gpio_pin, gpio_state);

  res.status = 200;
  res.status_msg = "OK";
  res.data = "Wrote " + to_string(gpio_state) + " to pin " + to_string(gpio_pin);

}
