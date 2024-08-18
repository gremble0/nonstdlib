#include <stdlib.h>

#include "nonstdlib/narena.h"
#include "nonstdlib/nerror.h"

arena_t *arena_init(size_t init_size) {
  arena_t *arena = malloc(sizeof(*arena));
  if (arena == NULL)
    err_malloc_fail();

  arena->size = 0;
  arena->capacity = init_size;
  arena->memory = malloc(init_size);
  if (arena->memory == NULL)
    err_malloc_fail();

  return arena;
}

void *arena_alloc(arena_t *arena, size_t num_bytes) {
  arena->size += num_bytes;
  if (arena->size > arena->capacity) {
    arena->memory = realloc(arena, arena->capacity *= 2);
    if (arena->memory == NULL)
      err_malloc_fail();
  }

  return arena->memory + arena->size;
}

void arena_free(arena_t *arena) {
  free(arena->memory);
  free(arena);
}
