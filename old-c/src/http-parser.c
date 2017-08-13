#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "http-parser.h"

request httpd_parse_request(char *buffer) {
  request req;
  char httpd_method[5];
  array *lines;
  unsigned int i;

  //Defaults.
  req.method = HTTPD_MTHD_UNKNOWN;

  //Split the buffer into an array of lines.
  lines = httpd_str_split("\n", buffer);

  //printf("The number of lines is: %zu\n", lines->size);
  for ( i=1; i<(lines->size); i++ ) {
    //printf("CHAR: %s\n", (char *)lines->array[i]);
  }

  //Detect request type.
  httpd_parse_request_head(&req, (char *)lines->array[1]);

  array_free(lines);

  return req;
}

/**
 * Splits a string by any delimiter as given in delim
 * into an array of strings
 */
array* httpd_str_split(char *delim, char *buffer)
{
  char *copied_buffer = malloc( strlen(buffer) * sizeof(char) + 1);
  array *result = malloc(sizeof(array));
  bzero(result, sizeof(array));

  char * pch;

  bzero(copied_buffer, strlen(buffer) * sizeof(char) +1);
  memcpy(copied_buffer, buffer, strlen(buffer) * sizeof(char));

  //Store results in array.
  array_init(result);

  pch = strtok (copied_buffer,delim);
  while (pch != NULL)
  {
    //Prepare the array entry
    char *entry = malloc( strlen(pch) * sizeof(char) + 1);
    bzero(entry, strlen(pch) * sizeof(char) + 1);

    strncpy(entry, (char *)pch, strlen(pch));

    //Append the line in the array.
    array_append(result, entry);

    printf ("%s\n",pch);
    pch = strtok (NULL, delim);
    free(entry);

  } 

  free(copied_buffer);

  return result;

}

void httpd_parse_request_head(request *req, char *line)
{
  array *args;
  array *uri_args;
  char *uri;
  unsigned int i;

  //Split the line by spaces.
  args = httpd_str_split(" ", line);
  printf("Size: %i\n", args->size);

  //Must have 4 arguments, "{method} {uri} {version}"
  if ( args->size < 4 ) 
  {
    req->error = 1;
    return;
  }

  //Method type
  if ( strcmp((char *)args->array[1], "GET") == 0 )
  {
    req->method = HTTPD_MTHD_GET;
  }
  else if ( strcmp((char *)args->array[1], "POST") == 0 )
  {
    req->method = HTTPD_MTHD_POST;
  } 

  //URI
  uri = malloc(1 + strlen((const char *)args->array[2]));
  bzero(uri, 1 + strlen((const char *)args->array[2]));
  strncpy(uri, (char *)args->array[2], strlen((const char *)args->array[2]));
  req->uri = uri;

  //Determine if GET is special case (i.e. /gpio/*)
  printf("METHOD: %s\n", req->method);
  if ( req->method == HTTPD_MTHD_GET )
  {
    uri_args = httpd_str_split("/", uri);
    if ( uri_args->size >= 3 )
    {
      if ( strcmp((char *)uri_args->array[1], "gpio") == 0 )
      {
        req->method = HTTPD_MTHD_GET_GPIO;
      }
    }
    free(uri_args);
  }

  //HTTP version.
  printf("URI: %s\n", (char *)args->array[2]);
  printf("Version: '%s'\n", (char *)args->array[3]);
  if ( strcmp((char *)args->array[3], "HTTP/1.0") != 0 &&
       strcmp((char *)args->array[3], "HTTP/1.1") != 0 )
  {
    puts("Unsupported HTTP version");
    //Unsupported HTTP version.
    req->error = 1;
    return;
  }

  array_free(args);
}
