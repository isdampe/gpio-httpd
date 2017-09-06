#!/bin/bash

# Check for wiringPi
HAS_WIRING_PI=$(/sbin/ldconfig -p | grep wiringPi | wc -l)
if [ $HAS_WIRING_PI -lt 1 ]
  then
  echo "Please install wiringPi to continue - http://wiringpi.com/download-and-install/."
  exit 1
fi

mkdir -p bin

if [ -f "bin/gpio-httpd" ] ; then
  echo "Removing stale binary for rebuild."
  rm bin/gpio-httpd
fi

echo "Running the compiler..."
g++-5 src/*.cpp -std=c++11 -lpthread -lwiringPi -lcrypt -lrt -g -o bin/gpio-httpd

echo "Compilation complete."
echo "Run with ./bin/gpio-httpd [port] [document_root_fp]"
echo "Example: ./bin/gpio-httpd 9001 $PWD/www"
