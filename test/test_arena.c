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
  strncpy(arena_string, "hello", sizeof("hello"));
  DEBUG_ASSERT(strncmp(arena_string, "hello", sizeof("hello")) == 0);

  arena_free(arena);
}

// TODO: this is not right, we cannot return pointers directly in arena_alloc i guess (can get moved
// when reallocing)
static void test_arena_alloc_expand(void) {
  const int arena_init_size = 128;
  arena_t *arena = arena_init(arena_init_size);

  int *some_memory = arena_alloc(arena, 64);
  *some_memory = 42;
  int *some_more_memory = arena_alloc(arena, 128);
  *some_more_memory = 69;

  DEBUG_ASSERT(arena->capacity != arena_init_size);
  DEBUG_ASSERT(*some_memory == 42);
  DEBUG_ASSERT(*some_more_memory == 69);

  arena_free(arena);
}

void test_arena(void) {
  TEST_MODULE_START("arena");

  test_arena_alloc();
  test_arena_alloc_expand();

  TEST_MODULE_END("arena");
}
