#ifndef LIST_H
#define LIST_H

#include "iterator.h"

typedef struct {
  // Put your fields here
} List;

List* newEmptyList();
List* prepend(List* head, int item);
void deinitList(List* head);
Iterator iterateList(List* head);

#endif
