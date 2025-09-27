#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct List;
struct LazyNode;

typedef struct {
  union ThunkCtx {
    int gen;

    struct {
      struct LazyNode* node;
      size_t left;
    } take;
  } ctx;
  struct List* (*func)(void*);
} Thunk;

struct List* runThunk(Thunk* t) {
  return t->func(&t->ctx);
}

typedef struct LazyNode {
  bool computed;

  union {
    struct List* value;
    Thunk thunk;
  } computation;
} LazyNode;

typedef struct List {
  int value;
  LazyNode next;
} List;

List* nextNode(void* px) {
  List* node = malloc(sizeof(List));

  int x = ((union ThunkCtx*) px)->gen;
  node->value = x;
  node->next = (LazyNode) {
      .computed = false,
      .computation = {.thunk = (Thunk) {.ctx = {.gen = x + 1}, .func = nextNode}},
  };
  return node;
}

LazyNode initList(int initial) {
  return (LazyNode) {
      .computed = false,
      .computation = {.thunk = (Thunk) {.ctx = {.gen = initial}, .func = nextNode}},
  };
}

void deinitLazyList(LazyNode head) {
  LazyNode cur = head;

  while (cur.computed && cur.computation.value) {
    List* cur_node = cur.computation.value;
    LazyNode next = cur_node->next;
    free(cur.computation.value);
    cur = next;
  }
}

void force(LazyNode* l) {
  assert(!l->computed);

  l->computed = true;
  l->computation.value = runThunk(&l->computation.thunk);
}

void forEach(LazyNode* l, void (*f)(int)) {
  for (;;) {
    if (!l->computed) {
      force(l);
    }

    List* cur = l->computation.value;
    if (!cur)
      return;

    f(cur->value);
    l = &cur->next;
  }
}

void printInt(int x) {
  printf("%d ", x);
}

List* nextTakeNode(void* ctx) {
  LazyNode* lazy_node = ((union ThunkCtx*) ctx)->take.node;
  size_t n = ((union ThunkCtx*) ctx)->take.left;

  if (n == 0) {
    return NULL;
  }

  List* res = malloc(sizeof(List));

  if (!lazy_node->computed)
    force(lazy_node);

  List* node = lazy_node->computation.value;
  res->value = node->value;

  Thunk thunk = (Thunk) {.ctx = {.take = {.node = &node->next, .left = n - 1}}, .func = nextTakeNode};
  res->next = (LazyNode) {.computed = false, .computation = {.thunk = thunk}};

  return res;
}

LazyNode take(LazyNode* l, size_t n) {
  return (LazyNode) {
      .computed = false,
      .computation = {
          .thunk = (Thunk) {.ctx = {.take = {.node = l, .left = n}}, .func = nextTakeNode},
      },
  };
}

int main() {
  size_t n;
  scanf("%zu", &n);

  LazyNode l = initList(0);
  LazyNode first10 = take(&l, 10);
  forEach(&first10, printInt);
  putchar('\n');

  deinitLazyList(l);
  deinitLazyList(first10);

  return 0;
}
