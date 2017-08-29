#include <map>
#include <string>
#include <vector>
#include "http-types.h"
#include "http-gpio.h"
#include "string_ops.h"
#include "map_ops.h"
#include <wiringPi.h>

using std::string;
using std::map;

void http_build_gpio_get_response(const http_request &req, http_response &res)
{
  vector<unsigned short> gpio_queries;
  vector<string> requested_pins;
  int gpio_pin = -1;
  map<string,string> json_data;
  wiringPiSetup();

  res.content_type = "application/json; charset=utf8";

  vector<string> uri_components = string_split_to_vector(req.uri, '/');
  if ( uri_components.size() != 2 )
  {
    //All pins.
    for ( int i=1; i<=31; i++ )
    {
      gpio_queries.push_back(i);
    }
  }
  else
  {

    requested_pins = string_split_to_vector(uri_components[1], ',');
    if ( requested_pins.size() > 0 )
    {
      for ( int k=0; k<requested_pins.size(); k++ )
      {
        //Convert the chosen pin to an integer.
        try {
          gpio_pin = stoi(requested_pins[k].c_str(), nullptr);
        } catch ( invalid_argument e ) {
          continue;
        }

        //Skip pins out of domain
        if ( gpio_pin < 0 || gpio_pin > 31 )
          continue;

        gpio_queries.push_back(gpio_pin);

      }
    }

  }

  if ( gpio_queries.size() < 1 )
  {
    res.status = 400;
    json_data["message"] = "No pins were selected for query.";
    res.data = map_to_json_string(json_data);
    return;
  }

  json_data = http_gpio_query_pins_to_map(gpio_queries);

  res.status = 200;
  res.status_msg = "OK";
  res.data = map_to_json_string(json_data);

}

void http_build_gpio_post_response(const http_request &req, http_response &res)
{
  int gpio_pin, gpio_state;
  map<string,string> json_data;
  wiringPiSetup();

  res.content_type = "application/json; charset=utf8";

  vector<string> uri_components = string_split_to_vector(req.uri, '/');
  if ( uri_components.size() != 3 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    json_data["message"] = "Missing pin or pin status.";
    res.data = map_to_json_string(json_data);
    return;
  }

  //Convert the chosen pin to an integer.
  try {
    gpio_pin = stoi(uri_components[1].c_str(), nullptr);
  } catch ( invalid_argument e ) {
    gpio_pin = -1;
  }

  //Check to see if the pin number is valid as a digital pin.
  if ( gpio_pin < 0 || gpio_pin > 31 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    json_data["message"] = "The requested pin is out of range [0-31].";
    res.data = map_to_json_string(json_data);
    return;
  }

  //Convert the state request to an integer.
  try {
    gpio_state = stoi(uri_components[2].c_str(), nullptr);
  } catch( invalid_argument e ) {
    gpio_state = -1;
  }

  if ( gpio_state < 0 || gpio_state > 1 )
  {
    res.status = 400;
    res.status_msg = "Bad Request";
    json_data["message"] = "The requested pin status must either be 0 or 1.";
    res.data = map_to_json_string(json_data);
    return;
  }

  //Set the pin mode to input for reading.
  pinMode(gpio_pin, OUTPUT);

  //Write to the pin.
  digitalWrite(gpio_pin, gpio_state);

  json_data[to_string(gpio_pin)] = to_string(gpio_state);

  res.status = 200;
  res.status_msg = "OK";
  res.data = map_to_json_string(json_data);

}


map<string,string> http_gpio_query_pins_to_map(const vector<unsigned short> &gpio_queries)
{
  map<string,string> results;
  int gpio_state;

  for ( int i=0; i<gpio_queries.size(); i++ )
  {
    //Reset
    gpio_state = -1;

    //Only query raspberry pi pins.
    if ( gpio_queries[i] < 1 || gpio_queries[i] > 31 )
      continue;

    //Set the pin mode to input for reading.
    pinMode(gpio_queries[i], INPUT);

    //Read the value of the pin.
    gpio_state = digitalRead(gpio_queries[i]);

    //Store the results in the map
    results[to_string(gpio_queries[i])] = to_string(gpio_state);

  }

  return results;

}
