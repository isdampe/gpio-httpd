import * from gpioAjax as ajax

class gpioApi {

  /**
   * Constructs a new gpioApi instance.
   * @param  {string} server The server address to connect to.
   * @param  {number} port   The port number to use.
   * @return {gpioApi}       The new gpioApi instance.
   */
  constructor(server = "localhost", port = null) {
    this.server = server;
    this.port = port;
  }

  /**
   * Writes a digital value to a remote GPIO pin.
   * @param  {number} pin   The pin number to write to [1-31].
   * @param  {number} value The value to write to the pin [1|0].
   * @return {void}
   */
  digitalWrite(pin, value) {

  }

  /**
   * Reads a digital value from a remote GPIO pin.
   * @param  {number} pin The pin number to read from [1-31].
   * @return {int}        The value read from the remote pin [1|0].
   */
  digitalRead(pin) {

  }

  /**
   * Sets the read mode for gpio-httpd
   * @param {string} mode The read-mode to use [emulated|digital|analogue]
   * @return {void}
   */
  setHttpdReadMode(mode) {

  }

}
