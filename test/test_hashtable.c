#include <stdio.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable.h"
#include "test.h"

void test_hashtable_int(void) {
  ht_t *table = ht_init(5);

  int a = 4;
  int b = 0;
  int c = 9;

  ht_put(table, "asd", strlen("asd") + 1, &a, sizeof(int));
  DEBUG_ASSERT(table->n_entries == 1);
  ht_put(table, "bbb", strlen("bbb") + 1, &b, sizeof(int));
  DEBUG_ASSERT(table->n_entries == 2);
  ht_put(table, "bbb", strlen("bbb") + 1, &c, sizeof(int));
  DEBUG_ASSERT(table->n_entries == 2);

  DEBUG_ASSERT(*(int *)ht_get(table, "asd", strlen("asd") + 1) == 4);
  DEBUG_ASSERT(*(int *)ht_get(table, "bbb", strlen("bbb") + 1) == 9);

  ht_free(table);
}

void test_hashtable_string(void) {
  ht_t *table = ht_init(5);

  ht_put(table, "asd", strlen("asd") + 1, "YOYO", strlen("YOYO") + 1);
  DEBUG_ASSERT(table->n_entries == 1);
  ht_put(table, "asd", strlen("asd") + 1, "YAYA", strlen("YAYA") + 1);
  DEBUG_ASSERT(table->n_entries == 1);
  ht_put(table, "qwerty", strlen("qwerty") + 1, "123", strlen("123") + 1);
  DEBUG_ASSERT(table->n_entries == 2);
  ht_put(table, "qwertz", strlen("qwertz") + 1, "BABA", strlen("BABA") + 1);
  DEBUG_ASSERT(table->n_entries == 3);
  ht_put(table, "qwertyb", strlen("qwertyb") + 1, "POPO", strlen("POPO") + 1);
  DEBUG_ASSERT(table->n_entries == 4);

  DEBUG_ASSERT(strcmp(ht_get(table, "asd", strlen("asd") + 1), "YAYA") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, "qwerty", strlen("qwerty") + 1), "123") ==
               0);
  DEBUG_ASSERT(strcmp(ht_get(table, "qwertz", strlen("qwertz") + 1), "BABA") ==
               0);
  DEBUG_ASSERT(table->max_entries == 10);

  ht_put(table, "iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur",
         strlen("iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur") + 1,
         "POPO", strlen("POPO") + 1);
  DEBUG_ASSERT(table->n_entries == 5);
  ht_put(table, "", strlen("") + 1,
         "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj",
         strlen("qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj") +
             1 + 1);
  DEBUG_ASSERT(table->n_entries == 6);
  DEBUG_ASSERT(table->max_entries == 20);

  DEBUG_ASSERT(ht_get(table, "doesnt_exist", strlen("doesnt_exist") + 1) ==
               NULL);

  ht_free(table);
}

void test_hashtable() {
  TEST_MODULE_START("hashtable");

  test_hashtable_int();
  test_hashtable_string();

  TEST_MODULE_END("hashtable");
}
