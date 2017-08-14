#!/bin/bash
mkdir -p bin
rm bin/gpio-httpd
clang++ src/*.cpp -std=c++11 -lpthread -g -o bin/gpio-httpd
