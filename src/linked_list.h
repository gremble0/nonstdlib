#pragma once

#include <stddef.h>

// TODO: make linked list, make this not linked list

typedef struct ll_entry_t {
    const void *value;
    struct ll_entry_t *next;
} ll_entry_t;

typedef struct ll_t {
    ll_entry_t *first;
    size_t size;
} ll_t;

ll_t *ll_init(void);
void ll_free(ll_t *ll);
const void *ll_peek(ll_t *ll);
const void *ll_pop(ll_t *ll);
const void *ll_seek(ll_t *ll, int index);
void ll_append(ll_t *ll, void *value);
