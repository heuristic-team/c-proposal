#include "list.h"

#include <stddef.h>
#include <stdlib.h>

List* newEmptyList() { return NULL; }

List* prepend(List* head, int item) {
  List* res = malloc(sizeof(List));
  res->next = head;
  res->value = item;
  return res;
}

void deinitList(List* head) {
  while (head) {
    List* next = head->next;
    free(head);
    head = next;
  }
}

static int listIteratorNext(Iterator* it) {
  const List* node = it->ctx;
  int res = node->value;
  it->ctx = node->next;
  return res;
}

static bool listIteratorHasNext(const Iterator* it) {
  return it->ctx != NULL;
}

static void deinitListIterator(Iterator* it) { (void) it; }

Iterator iterateList(List* head) {
  return (Iterator) {
      .ctx = head,
      .next = listIteratorNext,
      .hasNext = listIteratorHasNext,
      .deinit = deinitListIterator,
  };
}
