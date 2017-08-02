#include <stddef.h>

#ifndef TINYARR_INIT__
#define TINYARR_INIT__

typedef struct array {
  int **array;
  size_t size;
} array;

void array_init(array *a);
void array_append(array *a, char *s);
void array_free(array *a);

#endif /* TINYARR_INIT__*/

