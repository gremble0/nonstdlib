#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable_generic.h"
#include "test.h"

ht_prototype(int);
ht_impl(int);

typedef char *str;
ht_prototype(str);
ht_impl(str);

// int tests_passed = 0;
// int tests_ran = 0;

void test_hashtable_generic(void) {
  TEST_MODULE_START("generic hash table");

  int_ht_t *int_table = int_ht_init(5);
  int asd = 44;
  int_ht_put(int_table, "asd", &asd);
  assert(int_table->n_entries == 1);

  int asd2 = 22;
  int_ht_put(int_table, "asd", &asd2);
  assert(int_table->n_entries == 1);
  assert(*int_ht_get(int_table, "asd") == 22);

  str_ht_t *str_table = str_ht_init(5);
  str asd_str = "yoyo";
  str_ht_put(str_table, "asd", &asd_str);
  assert(str_table->n_entries == 1);
  assert(strcmp(*str_ht_get(str_table, "asd"), "yoyo") == 0);
  str qwerty = "zaza";
  str_ht_put(str_table, "z", &qwerty);
  assert(str_table->n_entries == 2);
  assert(strcmp(*str_ht_get(str_table, "asd"), "yoyo") == 0);
  assert(strcmp(*str_ht_get(str_table, "z"), "zaza") == 0);

  // TEST_MODULE_END("generic hash table");
}
