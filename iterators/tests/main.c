#include "../api.h"

#include <stddef.h>
#include <stdio.h>

static void printInt(int x) {
  printf("%d ", x);
}

static void printAll(struct Iterator* iter) {
  forEach(iter, printInt);
  putchar('\n');
}

static int add42(int x) {
  return x + 42;
}

static struct List* readList() {
  struct List* res = initList();

  int x;
  for (;;) {
    scanf("%d", &x);
    if (x == 0)
      break;
    res = prepend(res, x);
  }

  return res;
}

int main() {
  struct List* list = readList();
  struct Iterator* list_iter = iterateList(list);

  printAll(list_iter);

  deinitListIterator(list_iter);
  list_iter = iterateList(list);

  struct Iterator* mapped = map(list_iter, add42);
  printAll(mapped);

  deinitMap(mapped);
  deinitListIterator(list_iter);
  deinitList(list);

  return 0;
}
