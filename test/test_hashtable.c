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
  char asd[] = "asd";
  char bbb[] = "bbb";

  ht_put(table, asd, sizeof(asd), &a);
  DEBUG_ASSERT(table->cur_size == 1);
  ht_put(table, bbb, sizeof(bbb), &b);
  DEBUG_ASSERT(table->cur_size == 2);
  ht_put(table, bbb, sizeof(bbb), &c);
  DEBUG_ASSERT(table->cur_size == 2);

  DEBUG_ASSERT(*(int *)ht_get(table, "asd", sizeof(asd)) == 4);
  DEBUG_ASSERT(*(int *)ht_get(table, "bbb", sizeof(bbb)) == 9);

  ht_free(table);
}

void test_hashtable_string(void) {
  ht_t *table = ht_init(5);

  char asd[] = "asd";
  char qwerty[] = "qwerty";
  char qwertz[] = "qwertz";
  char qwertb[] = "qwertb";
  char longstring[] = "iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur";

  ht_put(table, asd, sizeof(asd), "YOYO");
  DEBUG_ASSERT(table->cur_size == 1);
  ht_put(table, asd, sizeof(asd), "YAYA");
  DEBUG_ASSERT(table->cur_size == 1);
  ht_put(table, qwerty, sizeof(qwerty), "123");
  DEBUG_ASSERT(table->cur_size == 2);
  ht_put(table, qwertz, sizeof(qwertz), "BABA");
  DEBUG_ASSERT(table->cur_size == 3);
  ht_put(table, qwertb, sizeof(qwertb), "POPO");
  DEBUG_ASSERT(table->cur_size == 4);

  DEBUG_ASSERT(strcmp(ht_get(table, asd, sizeof(asd)), "YAYA") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, qwerty, sizeof(qwerty)), "123") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, qwertz, sizeof(qwertz)), "BABA") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, qwertb, sizeof(qwertb)), "POPO") == 0);
  DEBUG_ASSERT(table->max_size == 10);

  ht_put(table, longstring, sizeof(longstring), "POPO");
  DEBUG_ASSERT(table->cur_size == 5);
  ht_put(table, "", sizeof(""),
         "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj");
  DEBUG_ASSERT(table->cur_size == 6);
  DEBUG_ASSERT(table->max_size == 20);

  DEBUG_ASSERT(ht_get(table, "doesnt_exist", sizeof("doesnt_exist")) == NULL);

  ht_free(table);
}

void test_hashtable() {
  TEST_MODULE_START("hashtable");

  test_hashtable_int();
  test_hashtable_string();

  TEST_MODULE_END("hashtable");
}
