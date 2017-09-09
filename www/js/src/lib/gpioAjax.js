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
    req.setRequestHeader('Content-Type', 'application/x-www-form-urlencoded');
    req.send();
  }

};
