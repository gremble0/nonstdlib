#pragma once

#include <stddef.h>

typedef struct {
  void *memory;
  size_t size;
  size_t capacity;
} arena_t;

arena_t *arena_init(size_t init_size);
void *arena_alloc(arena_t *arena, size_t num_bytes);
void arena_free(arena_t *arena);
