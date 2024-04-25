#include <stdio.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nstring.h"
#include "test.h"

void test_string_of(void) {
  const char s[] = "Hello, World";
  string_t *str = string_of(s, sizeof(s) - 1);

  DEBUG_ASSERT(strlen(s) == str->len);
  DEBUG_ASSERT(strncmp(str->s, s, str->len) == 0);

  string_t *str_copy = string_of(str->s, str->len);
  DEBUG_ASSERT(str_copy->len == str->len);
  DEBUG_ASSERT(strncmp(str_copy->s, str->s, str_copy->len) == 0);

  string_free(str);
  string_free(str_copy);
}

void test_string_clear(void) {
  const char s[] = "Nonstdlib";
  string_t *str = string_of(s, sizeof(s) - 1);

  string_clear(str);
  DEBUG_ASSERT(str->s == NULL);
  DEBUG_ASSERT(str->len == 0);

  string_free(str);
}

void test_string_set(void) {
  const char s1[] = "Nonstdlib";
  const char s2[] = "Nonstdlib version 2";
  string_t *str = string_of(s1, sizeof(s1) - 1);

  string_set(str, s2, sizeof(s2) - 1);
  DEBUG_ASSERT(strncmp(str->s, s2, str->len) == 0);

  string_free(str);
}

void test_string(void) {

  TEST_MODULE_START("string");

  test_string_of();
  test_string_clear();
  test_string_set();

  TEST_MODULE_END("string");
}
