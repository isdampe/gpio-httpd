#!/bin/bash
mkdir -p bin
rm bin/httpd
clang++ src/*.cpp -o bin/gpio-httpd
