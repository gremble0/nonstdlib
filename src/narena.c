#include <stdlib.h>

#include "nonstdlib/narena.h"

arena_t *arena_init(size_t init_size) {
  arena_t *arena = malloc(init_size);
  arena->size = 0;
  arena->capacity = init_size;
  return arena;
}

void *arena_alloc(arena_t *arena, size_t num_bytes) {
  arena->size += num_bytes;
  if (arena->size > num_bytes)
    arena->memory = realloc(arena, arena->capacity *= 2);

  return arena->memory + arena->size;
}

void arena_free(arena_t *arena) {
  free(arena->memory);
  free(arena);
}
