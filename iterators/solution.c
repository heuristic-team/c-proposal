#include "api.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool defined;
  int value;
} Option;

#define None ((Option) {.defined = false})

static Option Some(int x) { return (Option) {
    .defined = true,
    .value = x,
}; }

typedef struct Iterator {
  void* ctx;
  Option (*next)(struct Iterator*);
} Iterator;

static Option next(Iterator* it) {
  return it->next(it);
}

void forEach(Iterator* iter, void (*func)(int)) {
  Option cur;
  while ((cur = next(iter)).defined) {
    func(cur.value);
  }
}

typedef struct {
  Iterator* iter;
  int (*func)(int);
} MapCtx;

static Option Map_next(Iterator* self) {
  MapCtx* ctx = self->ctx;

  Option opt = next(ctx->iter);
  if (opt.defined) {
    return Some(ctx->func(opt.value));
  }

  return None;
}

Iterator* map(Iterator* iter, int (*func)(int)) {
  MapCtx* ctx = malloc(sizeof(MapCtx));
  *ctx = (MapCtx) {.func = func, .iter = iter};

  Iterator* res = malloc(sizeof(Iterator));
  *res = (Iterator) {.ctx = ctx, .next = Map_next};
  return res;
}

void deinitMap(Iterator* self) {
  free(self->ctx);
  free(self);
}

typedef struct List {
  int value;
  struct List* next;
} List;

List* initList() { return NULL; }

List* prepend(List* head, int item) {
  List* res = malloc(sizeof(List));
  res->next = head;
  res->value = item;
  return res;
}

void deinitList(List* l) {
  List* cur = l;
  while (cur) {
    List* next = cur->next;
    free(cur);
    cur = next;
  }
}

static Option ListIter_next(Iterator* self) {
  List* node = self->ctx;

  if (!node) {
    return None;
  }
  int res = node->value;
  self->ctx = node->next;
  return Some(res);
}

Iterator* iterateList(List* list) {
  Iterator* res = malloc(sizeof(Iterator));
  *res = (Iterator) {.ctx = list, .next = ListIter_next};
  return res;
}

void deinitListIterator(Iterator* iter) { free(iter); }
