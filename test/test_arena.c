#include <string.h>

#include "narena.h"
#include "nerror.h"
#include "test.h"

static void test_arena_alloc(void) {
  arena_t *arena = arena_init(1024);

  int *arena_int = arena_alloc(arena, sizeof(int));
  *arena_int = 4;
  DEBUG_ASSERT(*arena_int == 4);

  const char hello_world[] = "hello, world";

  char *arena_string = arena_alloc(arena, sizeof(hello_world));
  memcpy(arena_string, "hello", sizeof("hello"));
  DEBUG_ASSERT(strncmp(arena_string, "hello", sizeof("hello")) == 0);

  arena_free(arena);
}

static void test_arena_alloc_expand(void) {
  const int arena_init_size = 128;
  arena_t *arena = arena_init(arena_init_size);

  int *some_memory = arena_alloc(arena, 64);
  *some_memory = 42;
  // First allocation should not need to expand arena and should allocate in the first arena
  DEBUG_ASSERT(*some_memory == 42);
  DEBUG_ASSERT(arena->size == 64);
  DEBUG_ASSERT(arena->capacity == arena_init_size);
  DEBUG_ASSERT(arena->next == NULL);
  // Should be at the start of the first arenas memory
  DEBUG_ASSERT(some_memory == arena->memory);

  // Second allocation should need a minor expansion and end up allocating in a second linked arena
  int *some_more_memory = arena_alloc(arena, 128);
  *some_more_memory = 69;
  DEBUG_ASSERT(*some_more_memory == 69);
  DEBUG_ASSERT(arena->next != NULL);
  DEBUG_ASSERT(arena->next->size == 128);
  DEBUG_ASSERT(arena->next->capacity == arena_init_size * 2);
  // Should be at the start of the second arenas memory
  DEBUG_ASSERT(some_more_memory == arena->next->memory);

  // Third allocation should need another major expansion and end up allocating in a third linked
  // arena
  int *lots_of_memory = arena_alloc(arena, 1024);
  *lots_of_memory = 420;
  DEBUG_ASSERT(*lots_of_memory == 420);
  DEBUG_ASSERT(arena->next->next != NULL);
  DEBUG_ASSERT(arena->next->next->size == 1024);
  // Capacity should be the same as the second arena squared until its larger than allocation size
  DEBUG_ASSERT(arena->next->next->capacity == 128 * 2 * 2 * 2 * 2);
  // Should be at the start of the third arenas memory
  DEBUG_ASSERT(lots_of_memory == arena->next->next->memory);

  // Smaller allocations should fit into the first available arena
  int *a_little_memory = arena_alloc(arena, 16);
  *a_little_memory = 19;
  DEBUG_ASSERT(*a_little_memory == 19);
  DEBUG_ASSERT(arena->size == 64 + 16);
  DEBUG_ASSERT(a_little_memory == arena->memory + 64);

  arena_free(arena);
}

void test_arena(void) {
  TEST_MODULE_START("arena");

  test_arena_alloc();
  test_arena_alloc_expand();

  TEST_MODULE_END("arena");
}
