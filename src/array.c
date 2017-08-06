#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "array.h"

void array_init(array *a)
{
  a->array = malloc(sizeof(char *));
  memset(a->array, 0, sizeof(char *));
  a->size = 1;
}

void array_append(array *a, char *s)
{
  a->size++;
  a->array = realloc(a->array, a->size * sizeof(char *));
  a->array[a->size -1] = (int *)s;
}

void array_free(array *a)
{
  for ( int i=1; i<(a->size); i++ ) {
    free(a->array[i]);
  }
  free(a->array);
  free(a);
}
