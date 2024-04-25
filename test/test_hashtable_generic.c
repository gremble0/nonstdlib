#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable_generic.h"
#include "test.h"

ht_prototype(int);
ht_impl(int);

ht_prototype(char);
ht_impl(char);

static void test_hashtable_int(void) {
  int_ht_t *int_table = int_ht_init(5);
  int asd = 44;
  int_ht_put(int_table, "asd", &asd, sizeof(asd));
  DEBUG_ASSERT(int_table->n_entries == 1);

  int asd2 = 22;
  int_ht_put(int_table, "asd", &asd2, sizeof(asd2));
  DEBUG_ASSERT(int_table->n_entries == 1);
  DEBUG_ASSERT(*int_ht_get(int_table, "asd") == 22);

  int_ht_free(int_table);
}

static void test_hashtable_string(void) {
  char_ht_t *char_table = char_ht_init(5);
  char *asd_str = "yoyo";
  char_ht_put(char_table, "asd", asd_str, strlen(asd_str) + 1);
  DEBUG_ASSERT(char_table->n_entries == 1);
  DEBUG_ASSERT(strcmp(char_ht_get(char_table, "asd"), "yoyo") == 0);

  char *qwerty = "zaza";
  char_ht_put(char_table, "z", qwerty, strlen(qwerty) + 1);
  DEBUG_ASSERT(char_table->n_entries == 2);
  DEBUG_ASSERT(strcmp(char_ht_get(char_table, "asd"), "yoyo") == 0);
  DEBUG_ASSERT(strcmp(char_ht_get(char_table, "z"), "zaza") == 0);

  char_ht_free(char_table);
}

void test_hashtable_generic() {
  TEST_MODULE_START("hashtable_generic");

  test_hashtable_int();
  test_hashtable_string();

  TEST_MODULE_END("hashtable_generic");
}
