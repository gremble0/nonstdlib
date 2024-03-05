#include <stdio.h>
#include <string.h>

#include "hashtable.h"
#include "test.h"

static int tests_passed = 0;
static int tests_ran = 0;

void test_hashtable(int *total_tests_ran, int *total_tests_passed) {
  TEST_MODULE_START();

  ht_t *table = ht_init(5);
  ht_put(table, "asd", "YOYO");
  ASSERT_TRUE(table->n_entries == 1);
  ht_put(table, "asd", "YAYA");
  ASSERT_TRUE(table->n_entries == 1);
  ht_put(table, "qwerty", "123");
  ASSERT_TRUE(table->n_entries == 2);
  ht_put(table, "qwertz", "BABA");
  ASSERT_TRUE(table->n_entries == 3);
  ht_put(table, "qwertyb", "POPO");
  ASSERT_TRUE(table->n_entries == 4);

  ASSERT_TRUE(strcmp(ht_get(table, "asd"), "YAYA") == 0);
  ASSERT_TRUE(strcmp(ht_get(table, "qwerty"), "123") == 0);
  ASSERT_TRUE(strcmp(ht_get(table, "qwertz"), "BABA") == 0);
  ASSERT_TRUE(table->max_entries == 10);

  ht_put(table, "iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur", "POPO");
  ASSERT_TRUE(table->n_entries == 5);
  ht_put(table, "", "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj");
  ASSERT_TRUE(table->n_entries == 6);
  ASSERT_TRUE(table->max_entries == 20);

  long a = 2;
  ht_put(table, "jig", &a);
  ASSERT_TRUE(*(long *)ht_get(table, "jig") == a);
  ASSERT_TRUE(ht_get(table, "doesnt_exist") == NULL);

defer:
  ht_free(table);

  TEST_FUNCTION_SUCCESS();
  TEST_MODULE_END();

  *total_tests_passed += tests_passed;
  *total_tests_ran += tests_ran;
}
