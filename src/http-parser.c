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

  printf("The number of lines is: %zu\n", lines->size);
  for ( i=1; i<(lines->size); i++ ) {
    printf("CHAR: %s\n", (char *)lines->array[i]);
  }

  //Detect request type.
  httpd_parse_request_head(&req, (char *)lines->array[1]);

  switch ( req.method ) {
    case HTTPD_MTHD_GET:
      puts("TYPE: GET");
      break;
  }

  printf("Request URI: %s\n", req.uri);

  array_free(lines);

  return req;
}

/**
 * Splits a string by any delimiter as given in delim
 * into an array of strings
 */
array* httpd_str_split(char *delim, char *buffer)
{
  char *copied_buffer;
  array *result = malloc(sizeof(array));
  char * pch;

  //Make a copy of the buffer to modify.
  copied_buffer = malloc(1 + strlen(buffer));
  strncpy(copied_buffer, buffer, strlen(buffer));

  //Store results in array.
  array_init(result);

  pch = strtok (copied_buffer,delim);
  while (pch != NULL)
  {
    //Prepare the array entry
    char *entry = malloc(1 + strlen(pch));
    bzero(entry, 1 + strlen(pch));

    strncpy(entry, pch, strlen(pch));

    //Append the line in the array.
    array_append(result, entry);

    //printf ("%s\n",pch);
    pch = strtok (NULL, delim);
  } 

  free(copied_buffer);

  return result;

}

void httpd_parse_request_head(request *req, char *line)
{
  array *args;
  char *uri;
  unsigned int i;

  //Split the line by spaces.
  args = httpd_str_split(" ", line);

  //Must have 4 arguments, "{method} {uri} {version}"
  if ( args->size < 4 ) 
  {
    req->error = 1;
    return;
  }

  //Method type
  //printf("Method: %s\n", (char *)args->array[1]);
  if ( strcmp((char *)args->array[1], "GET") == 0 )
  {
    req->method = HTTPD_MTHD_GET;
  }

  //URI
  uri = malloc(1 + strlen(args->array[2]));
  bzero(uri, 1 + strlen(args->array[2]));
  strncpy(uri, args->array[2], strlen(args->array[2]));
  req->uri = uri;

  //HTTP version.
  //printf("Version: %s\n", (char *)args->array[3]);
  if ( strcmp((char *)args->array[3], "HTTP/1.0") != 0 &&
       strcmp((char *)args->array[3], "HTTP/1.0") != 0 )
  {
    //puts("Unsupported HTTP version");
    req->error = 1;
    return;
  }

  array_free(args);
}
