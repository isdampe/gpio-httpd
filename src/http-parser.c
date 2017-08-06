#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "array.h"
#include "http-parser.h"

request httpd_parse_request(char *buffer) {
  request req;
  char httpd_method[5];
  array *lines;

  //Defaults.
  req.method = THTTP_METHOD_UNKNOWN;

  //Split the buffer into an array of lines.
  lines = httpd_str_split("\n", buffer);

  printf("The number of lines is: %zu\n", lines->size);
  for ( int i=1; i<(lines->size); i++ ) {
    printf("CHAR: %s\n", (char *)lines->array[i]);
  }

  //Detect request type.
  
  //

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

  array_init(result);
  pch = strtok (copied_buffer,delim);
  while (pch != NULL)
  {
    char *entry = malloc(strlen(pch));
    strncpy(entry, pch, strlen(pch));
    array_append(result, entry);
    //printf ("%s\n",pch);
    pch = strtok (NULL, delim);
  } 

  free(copied_buffer);

  return result;

}
