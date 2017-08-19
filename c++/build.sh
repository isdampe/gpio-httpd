#!/bin/bash
mkdir -p bin
rm bin/gpio-httpd
clang++ src/*.cpp -std=c++11 -lpthread -lwiringPi -lcrypt -lrt -g -o bin/gpio-httpd
# For raspberry pi
#g++-5 src/*.cpp -std=c++11 -lpthread -lwiringPi -lcrypt -lrt -g -o bin/gpio-httpd

# For wiringPi
# -lwiringPi
