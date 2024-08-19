#include <stdlib.h>

#include "nonstdlib/narena.h"
#include "nonstdlib/nerror.h"

arena_t *arena_init(size_t init_size) {
  arena_t *arena = malloc(sizeof(*arena));
  if (arena == NULL)
    err_malloc_fail();

  arena->size = 0;
  arena->capacity = init_size;
  arena->next = NULL;
  arena->memory = malloc(init_size);
  if (arena->memory == NULL)
    err_malloc_fail();

  return arena;
}

static arena_t *arena_first_available(arena_t *arena, size_t num_bytes) {
  arena_t *iter = arena;
  while (iter->size + num_bytes > iter->capacity)
    if (iter->next == NULL) {
      size_t next_capacity = iter->capacity * 2;
      // Just in case we need some ridiculously large amount of memory in one chunk
      while (next_capacity <= num_bytes)
        next_capacity *= 2;
      iter->next = arena_init(next_capacity);
      iter = iter->next;
      break;
    } else {
      iter = iter->next;
    }

  return iter;
}

void *arena_alloc(arena_t *arena, size_t num_bytes) {
  arena = arena_first_available(arena, num_bytes);
  void *allocation = arena->memory + arena->size;
  arena->size += num_bytes;

  return allocation;
}

void arena_free(arena_t *arena) {
  if (arena->next != NULL)
    arena_free(arena->next);

  free(arena->memory);
  free(arena);
}
