#pragma once

#include <stddef.h>

typedef struct ll_entry_t {
    const void *value;
    struct ll_entry_t *next;
    // TODO: struct ll_entry_t *prev;
} ll_entry_t;

typedef struct ll_t {
    ll_entry_t *first;
    // TODO: ll_entry_t *last;
    size_t size;
} ll_t;

void ll_append(ll_t *ll, const void *value);
ll_t *ll_init(void);
void ll_free(ll_t *ll);
const void *ll_peek(ll_t *ll);
const void *ll_pop(ll_t *ll);
const void *ll_seek(ll_t *ll, int index);
void ll_push(ll_t *ll, const void *value);
