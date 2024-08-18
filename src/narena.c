#include <stdlib.h>

#include "nonstdlib/narena.h"

arena_t *arena_init(size_t init_size) {
  arena_t *arena = malloc(init_size);
  arena->size = 0;
  arena->capacity = init_size;
  return arena;
}
