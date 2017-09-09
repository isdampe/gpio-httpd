(function e(t,n,r){function s(o,u){if(!n[o]){if(!t[o]){var a=typeof require=="function"&&require;if(!u&&a)return a(o,!0);if(i)return i(o,!0);var f=new Error("Cannot find module '"+o+"'");throw f.code="MODULE_NOT_FOUND",f}var l=n[o]={exports:{}};t[o][0].call(l.exports,function(e){var n=t[o][1][e];return s(n?n:e)},l,l.exports,e,t,n,r)}return n[o].exports}var i=typeof require=="function"&&require;for(var o=0;o<r.length;o++)s(r[o]);return s})({1:[function(require,module,exports){
const ajax = require('./lib/gpioAjax.js');

class gpioApi {

  /**
   * Constructs a new gpioApi instance.
   * @param  {string} server The server address to connect to.
   * @param  {number} port   The port number to use.
   * @return {gpioApi}       The new gpioApi instance.
   */
  constructor(server = "localhost", port = 9001) {
    this.server = server;
    this.port = port;
    this.base = "//" + server;
    if ( this.port !== 80 && this.port !== 443 )
      this.base += ":" + this.port;
    this.base += "/gpio/";
    this.gpioCache = {};
  }

  /**
   * Writes a digital value to a remote GPIO pin.
   * @param  {number}   pin       The pin number to write to [1-31].
   * @param  {number}   value     The value to write to the pin [1|0].
   * @param  {function} callback  The callback function handler.
   * @return {void}
   */
  digitalWrite(pin, value, callback) {
    if (! this.validatePin(pin) || ! this.validatePinValue(value) )
      return;

    if (typeof callback !== "function")
      callback = function(){};

    const uri = this.base + pin + "/" + value;

    this.gpioCache[pin] = value;
    ajax.post(uri, callback);

  }

  /**
   * Reads a digital value from a remote GPIO pin.
   * @param  {number}   pin       The pin number to read from [1-31].
   * @param  {function} callback  The callback(status, value) function handler.
   */
  digitalRead(pin, callback) {
    if (! this.validatePin(pin) || typeof callback !== "function" )
      return;

    const uri = this.base + pin;
    ajax.get(uri, callback);

  }

  /**
   * Reads a known GPIO value from cache.
   * @param  {number}   pin       The pin number to read from [1-31].
   * @param  {function} callback  The callback(status, value) function handler.
   * @return {mixed}              Void if a callback is provided, otherwise the result value.
   */
  cachedRead(pin, callback) {
    var result = 0;
    if ( this.gpioCache.hasOwnProperty(pin) )
      result = this.gpioCache[pin];

    if ( typeof callback === "function" )
      callback(result);
    else
      return result;
  }

  /**
   * Checks to ensure the pin number is in the domain of GPIO.
   * @param  {number} pin The pin number to validate.
   * @return {bool}       True if the pin is valid, otherwise false.
   */
  validatePin(pin) {
    if ( pin < 1 || pin > 31 ) {
      console.error("validatePin error: Pin number " + pin + " is out of bounds.");
      return false;
    }
    return true;
  }

  /**
   * Checks to ensure the pin value is in the domain of GPIO.
   * @param  {number} value The value to check.
   * @return {bool}         True if the value is valid, otherwise false.
   */
  validatePinValue(value) {
    value = parseInt(value);
    if ( value < 0 || value > 1 ) {
      console.error("validateValue error: Pin value " + value + " is out of bounds.");
      return false;
    }
    return true;
  }

}

window.gpioApi = gpioApi;

},{"./lib/gpioAjax.js":2}],2:[function(require,module,exports){
/**
 * Handles an AJAX response and decodes JSON data accordingly.
 * @param  {XMLHttpRequest}   req       The http request instance.
 * @param  {functoin}         callback  The callback function handler.
 * @return {void}
 */
var handleRequest = function(req, callback) {
  var json_res, error = 0;
  if (req.readyState !== XMLHttpRequest.DONE) return;

  if (req.status !== 200)
    error = req.status;

  try {
    json_res = JSON.parse(req.responseText);
  } catch(e) {
    json_res = {};
  }

  if ( typeof callback === "function" )
    callback(error, json_res);
};

module.exports = {

  /**
   * Performs an ajax HTTP GET request on a given uri.
   * @param  {string}   uri      The URI to perform the request on.
   * @param  {function} callback The callback function handler
   * @return {void}
   */
  get: (uri, callback) => {
    var req = new XMLHttpRequest();
    var _this = this;

    req.onreadystatechange = function() {
      handleRequest(req, callback);
    };

    req.open('GET', uri, true);
    req.send();
  },

  /**
   * Performs an ajax HTTP POST request on a given uri.
   * @param  {string}   uri      The URI to perform the request on.
   * @param  {object}   data     The object of data to send with the request.
   * @param  {function} callback The callback function handler
   * @return {void}
   */
  post: (uri, data, callback) => {
    var req = new XMLHttpRequest();
    var _this = this;

    req.onreadystatechange = function() {
      handleRequest(req, callback);
    };

    req.open('POST', uri, true);
    req.send();
  }
  
};

},{}]},{},[1]);
