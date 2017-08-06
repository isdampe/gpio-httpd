#!/bin/bash
mkdir -p bin
rm bin/httpd
gcc src/*.c -o bin/gpio-httpd -lpthread
