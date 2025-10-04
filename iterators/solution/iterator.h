#ifndef ITERATOR_H
#define ITERATOR_H

#include <stdbool.h>
#include <stddef.h>

typedef struct Iterator {
  void* ctx;
  bool (*hasNext)(const struct Iterator*);
  int (*next)(struct Iterator*);
  void (*deinit)(struct Iterator*);
} Iterator;

void forEach(Iterator it, void (*func)(int));
Iterator map(Iterator it, int (*func)(int));

#endif
