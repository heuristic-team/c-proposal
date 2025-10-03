#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>

typedef struct {
  // Put your fields here
} Iterator;

void forEach(Iterator it, void (*func)(int));
Iterator map(Iterator it, int (*func)(int));

#endif
