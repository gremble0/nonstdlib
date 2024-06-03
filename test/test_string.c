#include <stdio.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nstring.h"
#include "test.h"

static void test_string_of(void) {
  const char s[] = "Hello, World";
  string_t *str = string_of(s, sizeof(s));

  DEBUG_ASSERT(strlen(s) + 1 == str->len);
  DEBUG_ASSERT(strncmp(str->s, s, str->len) == 0);

  string_t *str_copy = string_of(str->s, str->len);
  DEBUG_ASSERT(str_copy->len == str->len);
  DEBUG_ASSERT(strncmp(str_copy->s, str->s, str_copy->len) == 0);

  string_free(str);
  string_free(str_copy);
}

static void test_string_clear(void) {
  const char s[] = "Nonstdlib";
  string_t *str = string_of(s, sizeof(s) - 1);

  string_clear(str);
  DEBUG_ASSERT(str->s == NULL);
  DEBUG_ASSERT(str->len == 0);

  string_free(str);
}

static void test_string_set(void) {
  const char s1[] = "Nonstdlib";
  const char s2[] = "Nonstdlib version 2";
  string_t *str = string_of(s1, sizeof(s1));

  string_set(str, s2, sizeof(s2));
  DEBUG_ASSERT(strncmp(str->s, s2, str->len) == 0);

  string_clear(str);
  string_set(str, s1, sizeof(s1));
  DEBUG_ASSERT(strlen(s1) + 1 == str->len);
  DEBUG_ASSERT(strncmp(str->s, s1, str->len) == 0);

  string_free(str);
}

static void test_string_compare(void) {
  const char s1[] = "Nonstdlib";
  const char s2[] = "nonstdlib";
  const char s3[] = "ns";
  const char s4[] = "N";
  const char s5[] = "N";

  string_t *str1 = string_of(s1, sizeof(s1));
  string_t *str2 = string_of(s2, sizeof(s2));
  string_t *str3 = string_of(s3, sizeof(s3));
  string_t *str4 = string_of(s4, sizeof(s4));
  string_t *str5 = string_of(s5, sizeof(s5));

  DEBUG_ASSERT(string_compare(str1, str1) == 0);
  DEBUG_ASSERT(string_compare(str1, str2) == 1);
  DEBUG_ASSERT(string_compare(str2, str1) == -1);
  DEBUG_ASSERT(string_compare(str1, str3) == -1);
  DEBUG_ASSERT(string_compare(str3, str4) == -1);
  DEBUG_ASSERT(string_compare(str4, str5) == 0);

  string_free(str1);
  string_free(str2);
  string_free(str3);
  string_free(str4);
  string_free(str5);
}

static void test_string_append(void) {
  const char s1[] = "Hello, ";
  const char s2[] = "world";

  string_t *str1 = string_of(s1, sizeof(s1));
  string_t *str2 = string_of(s2, sizeof(s2));
  string_t *str3 = string_of("", sizeof(""));
  string_t *expected1 = string_of("Hello, world", sizeof("Hello, world"));
  string_t *expected2 = string_of("Hello, world!", sizeof("Hello, world!"));

  string_append(str1, str2);
  DEBUG_ASSERT(string_compare(str1, expected1) == 0);
  string_append(str1, str3);
  DEBUG_ASSERT(string_compare(str1, expected1) == 0);

  string_append_c(str1, '!');
  DEBUG_ASSERT(string_compare(str1, expected2) == 0);

  string_free(str1);
  string_free(str2);
  string_free(str3);
  string_free(expected1);
  string_free(expected2);
}

static void test_string_copy(void) {
  const char s1[] = "Hello, ";

  string_t *str1 = string_of(s1, sizeof(s1));
  string_t *str1_copied = string_copy(str1);
  // The strings str1 and str1_copied should:
  // - not be pointing to the same memory
  // - not contain char pointers pointing to the same memory
  // - have the same lengths
  // - contain char pointers to identical strings
  DEBUG_ASSERT(str1 != str1_copied);
  DEBUG_ASSERT(str1->s != str1_copied->s);
  DEBUG_ASSERT(str1->len == str1_copied->len);
  DEBUG_ASSERT(string_compare(str1, str1_copied) == 0);

  // str1_copied should work after str1 has been freed
  string_free(str1);
  DEBUG_ASSERT(strncmp(str1_copied->s, s1, str1_copied->len) == 0);

  string_free(str1_copied);
}

static void test_string_lits(void) {
  string_t *s = string_of_lit("hello");
  string_t *same_as_s = string_of("hello", sizeof("hello"));

  DEBUG_ASSERT(string_compare(s, same_as_s) == 0);

  string_append_lit(s, ", world");
  string_append(same_as_s, &(string_t){", world", sizeof(", world")});

  DEBUG_ASSERT(string_compare(s, same_as_s) == 0);

  string_free(s);
  string_free(same_as_s);
}

void test_string(void) {

  TEST_MODULE_START("string");

  test_string_of();
  test_string_clear();
  test_string_set();
  test_string_compare();
  test_string_append();
  test_string_copy();
  test_string_lits();

  TEST_MODULE_END("string");
}
