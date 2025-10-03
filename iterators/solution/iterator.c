#include "iterator.h"

#include <stdlib.h>

void forEach(Iterator it, void (*func)(int)) {
  while (it.hasNext(&it)) {
    func(it.next(&it));
  }
  it.deinit(&it);
}

typedef struct {
  Iterator it;
  int (*f)(int);
} MapCtx;

static void deinitMap(Iterator* it) {
  MapCtx* ctx = it->ctx;
  ctx->it.deinit(&ctx->it);
  free(ctx);
}

static int mapNext(Iterator* it) {
  MapCtx* ctx = it->ctx;
  Iterator* underlyingIterator = &ctx->it;
  return ctx->f(underlyingIterator->next(underlyingIterator));
}

static bool mapHasNext(const Iterator* it) {
  const MapCtx* ctx = it->ctx;
  const Iterator* underlyingIterator = &ctx->it;
  return underlyingIterator->hasNext(underlyingIterator);
}

Iterator map(Iterator it, int (*func)(int)) {
  MapCtx* ctx = malloc(sizeof(MapCtx));
  ctx->f = func;
  ctx->it = it;
  return (Iterator) {
      .ctx = ctx,
      .next = mapNext,
      .hasNext = mapHasNext,
      .deinit = deinitMap,
  };
}
