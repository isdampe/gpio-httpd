#!/bin/bash
browserify www/js/src/gpioApi.js -o www/js/dist/gpio.js
sass -t compressed www/scss/style.scss www/css/style.css
