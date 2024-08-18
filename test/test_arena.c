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

  arena_free(arena);
}

void test_arena(void) {
  TEST_MODULE_START("arena");

  test_arena_alloc();

  TEST_MODULE_END("arena");
}
