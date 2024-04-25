#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nstring.h"
#include "test.h"

void test_string_of() {
  const char s[] = "Hello, World";
  string_t *str = string_of(s, sizeof(s) - 1);

  DEBUG_ASSERT(strncmp(str->s, s, str->len) == 0);
}

void test_string() {
  TEST_MODULE_START("string");

  test_string_of();

  TEST_MODULE_END("string");
}
