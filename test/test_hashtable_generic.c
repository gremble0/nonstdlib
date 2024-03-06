#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "hashtable_generic.h"
#include "test.h"

ht_prototype(int);
ht_impl(int);

ht_prototype(char);
ht_impl(char);

static int tests_passed = 0;
static int tests_ran = 0;

void test_hashtable_generic(int *total_tests_ran, int *total_tests_passed) {
  TEST_MODULE_START();

  int_ht_t *int_table = int_ht_init(5);
  int asd = 44;
  int_ht_put(int_table, "asd", &asd, sizeof(asd));
  ASSERT_TRUE(int_table->n_entries == 1);

  int asd2 = 22;
  int_ht_put(int_table, "asd", &asd2, sizeof(asd2));
  ASSERT_TRUE(int_table->n_entries == 1);
  ASSERT_TRUE(*int_ht_get(int_table, "asd") == 22);

  char_ht_t *char_table = char_ht_init(5);
  char *asd_str = "yoyo";
  char_ht_put(char_table, "asd", asd_str, strlen(asd_str) + 1);
  ASSERT_TRUE(char_table->n_entries == 1);
  ASSERT_TRUE(strcmp(char_ht_get(char_table, "asd"), "yoyo") == 0);
  char *qwerty = "zaza";
  char_ht_put(char_table, "z", qwerty, strlen(qwerty) + 1);
  ASSERT_TRUE(char_table->n_entries == 2);
  ASSERT_TRUE(strcmp(char_ht_get(char_table, "asd"), "yoyo") == 0);
  ASSERT_TRUE(strcmp(char_ht_get(char_table, "z"), "zaza") == 0);

defer:
  TEST_FUNCTION_SUCCESS();
  TEST_MODULE_END();

  *total_tests_passed += tests_passed;
  *total_tests_ran += tests_ran;
}
