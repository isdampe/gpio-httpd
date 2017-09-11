# gpio-httpd
A simple, lightweight HTTP server for the raspberry pi. Serve static files and
directly read / write GPIO pins via HTTP.

## Pre-requisites
To compile gpio-httpd on Raspbian Jessie, you will need:

* g++-5
* wiringPi (and development headers)

## Installing and compiling gpio-httpd
The best way to install and compile gpio-httpd is directly from source.

```bash
git clone https://github.com/isdampe/gpio-http -o gpio-httpd
cd gpio-httpd
git pull
# Before running the install script, view it first.
cat build-raspberry.sh
# Once you are happy with it, run it.
./build-raspberry.sh
```

## Running gpio-httpd
gpio-httpd can be run in user space via the terminal, or can be setup as a service using systemd or similar.

To run gpio-httpd, the syntax is

```bash
./gpio-httpd [port] [document_root]
```

To run gpio-httpd on port 9001 and serve the bundled www documents

```bash
./gpio-httpd 9001 /path/to/gpio-httpd/www
```

## Making GPIO requests
gpio-httpd loosely follows a RESTFUL API architecture. GPIO pins can be written
to or read from. Supported pins are 1-31 inclusive. All gpio requests are served as JSON and will respond with HTTP header Content-Type: application/json.

### Reading pins
Note: Calling this will set pinMode to INPUT for the specified pin(s).

__Reading all pin values:__  
```
Request:
GET /gpio HTTP/1.1

Response:
{"1": "0", "2": "0", ..., "31": "1"}
```

__Reading the value of pin 5:__
```
Request:
GET /gpio/5 HTTP/1.1

Response:
{"5": "1"}
```

__Read the value of pins 5, 3 and 10:__
```
Request:
GET /gpio/5,3,10 HTTP/1.1

Response:
{"5": "1", "3": "0", "10": "0"}
```

### Writing to pins
Note: Calling this will set pinMode to OUTPUT for the specified pin(s). Accepted values to write are 0 (LOW) or 1 (HIGH).

__Writing value 1 to pin 5:__
```
Request:
POST /gpio/5/1 HTTP/1.1

Response:
{"5": "1"}
```
