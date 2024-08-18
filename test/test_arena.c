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

static void test_arena_alloc_expand(void) {
  const int num_allocs = 50;
  const int arena_init_size = 128;
  arena_t *arena = arena_init(128);
  DEBUG_ASSERT(arena->capacity == arena_init_size);

  for (int i = 0; i < num_allocs; ++i) {
    int *arena_int = arena_alloc(arena, sizeof(*arena_int));
    *arena_int = i;
  }

  DEBUG_ASSERT(arena->capacity != arena_init_size);

  for (int i = 0; i < num_allocs; ++i) {
    // printf("%d\n", *(int *)(arena->memory + sizeof(int) * i));
    DEBUG_ASSERT(*(int *)(arena->memory + sizeof(int) * i) == i);
  }

  arena_free(arena);
}

void test_arena(void) {
  TEST_MODULE_START("arena");

  test_arena_alloc();
  test_arena_alloc_expand();

  TEST_MODULE_END("arena");
}
