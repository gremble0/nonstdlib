#include <stdio.h>
#include <string.h>

#include "nhashtable.h"
#include "test.h"

static int tests_passed = 0;
static int tests_ran = 0;

void test_hashtable_int(void) {
  ht_t *table = ht_init(5);

  int a = 4;
  int b = 0;
  int c = 9;

  ht_put(table, "asd", &a, sizeof(int));
  ASSERT_TRUE(table->n_entries == 1);
  ht_put(table, "bbb", &b, sizeof(int));
  ASSERT_TRUE(table->n_entries == 2);
  ht_put(table, "bbb", &c, sizeof(int));
  ASSERT_TRUE(table->n_entries == 2);

  ASSERT_TRUE(*(int *)ht_get(table, "asd") == 4);
  ASSERT_TRUE(*(int *)ht_get(table, "bbb") == 9);

defer:
  ht_free(table);

  TEST_FUNCTION_SUCCESS();
}

void test_hashtable_string(void) {
  ht_t *table = ht_init(5);

  ht_put(table, "asd", "YOYO", strlen("YOYO") + 1);
  ASSERT_TRUE(table->n_entries == 1);
  ht_put(table, "asd", "YAYA", strlen("YAYA") + 1);
  ASSERT_TRUE(table->n_entries == 1);
  ht_put(table, "qwerty", "123", strlen("123") + 1);
  ASSERT_TRUE(table->n_entries == 2);
  ht_put(table, "qwertz", "BABA", strlen("BABA") + 1);
  ASSERT_TRUE(table->n_entries == 3);
  ht_put(table, "qwertyb", "POPO", strlen("POPO") + 1);
  ASSERT_TRUE(table->n_entries == 4);

  ASSERT_TRUE(strcmp(ht_get(table, "asd"), "YAYA") == 0);
  ASSERT_TRUE(strcmp(ht_get(table, "qwerty"), "123") == 0);
  ASSERT_TRUE(strcmp(ht_get(table, "qwertz"), "BABA") == 0);
  ASSERT_TRUE(table->max_entries == 10);

  ht_put(table, "iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur", "POPO",
         strlen("POPO") + 1);
  ASSERT_TRUE(table->n_entries == 5);
  ht_put(table, "", "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj",
         strlen("qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj") +
             1);
  ASSERT_TRUE(table->n_entries == 6);
  ASSERT_TRUE(table->max_entries == 20);

  ASSERT_TRUE(ht_get(table, "doesnt_exist") == NULL);

defer:
  ht_free(table);

  TEST_FUNCTION_SUCCESS();
}

void test_hashtable(int *total_tests_ran, int *total_tests_passed) {
  TEST_MODULE_START();

  test_hashtable_int();
  test_hashtable_string();

  TEST_MODULE_END();

  *total_tests_passed += tests_passed;
  *total_tests_ran += tests_ran;
}
