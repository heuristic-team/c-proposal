#include "../iterator.h"
#include "../list.h"

#include <stddef.h>
#include <stdio.h>

static void printInt(int x) {
  printf("%d ", x);
}

static void printAll(Iterator iter) {
  forEach(iter, printInt);
  putchar('\n');
}

static int add42(int x) {
  return x + 42;
}

static List* readList() {
  List* res = newEmptyList();

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
  List* list = readList();
  Iterator listIter = iterateList(list);

  printAll(listIter);
  listIter = iterateList(list);

  Iterator mapped = map(listIter, add42);
  printAll(mapped);

  deinitList(list);
  return 0;
}
