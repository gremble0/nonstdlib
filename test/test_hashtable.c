#include <stdio.h>
#include <string.h>

#include "nerror.h"
#include "nhashtable.h"
#include "test.h"

void test_hashtable_int(void) {
  ht_t *table = ht_init(5);

  int a = 4;
  int b = 0;
  int c = 9;

  ht_put(table, "asd", &a, sizeof(int));
  DEBUG_ASSERT(table->n_entries == 1);
  ht_put(table, "bbb", &b, sizeof(int));
  DEBUG_ASSERT(table->n_entries == 2);
  ht_put(table, "bbb", &c, sizeof(int));
  DEBUG_ASSERT(table->n_entries == 2);

  DEBUG_ASSERT(*(int *)ht_get(table, "asd") == 4);
  DEBUG_ASSERT(*(int *)ht_get(table, "bbb") == 9);

  ht_free(table);
}

void test_hashtable_string(void) {
  ht_t *table = ht_init(5);

  ht_put(table, "asd", "YOYO", strlen("YOYO") + 1);
  DEBUG_ASSERT(table->n_entries == 1);
  ht_put(table, "asd", "YAYA", strlen("YAYA") + 1);
  DEBUG_ASSERT(table->n_entries == 1);
  ht_put(table, "qwerty", "123", strlen("123") + 1);
  DEBUG_ASSERT(table->n_entries == 2);
  ht_put(table, "qwertz", "BABA", strlen("BABA") + 1);
  DEBUG_ASSERT(table->n_entries == 3);
  ht_put(table, "qwertyb", "POPO", strlen("POPO") + 1);
  DEBUG_ASSERT(table->n_entries == 4);

  DEBUG_ASSERT(strcmp(ht_get(table, "asd"), "YAYA") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, "qwerty"), "123") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, "qwertz"), "BABA") == 0);
  DEBUG_ASSERT(table->max_entries == 10);

  ht_put(table, "iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur", "POPO",
         strlen("POPO") + 1);
  DEBUG_ASSERT(table->n_entries == 5);
  ht_put(table, "", "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj",
         strlen("qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj") +
             1);
  DEBUG_ASSERT(table->n_entries == 6);
  DEBUG_ASSERT(table->max_entries == 20);

  DEBUG_ASSERT(ht_get(table, "doesnt_exist") == NULL);

  ht_free(table);
}

void test_hashtable() {
  TEST_MODULE_START("hashtable");

  test_hashtable_int();
  test_hashtable_string();

  TEST_MODULE_END("hashtable");
}
