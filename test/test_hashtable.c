#include <stdio.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable.h"
#include "nonstdlib/nstring.h"
#include "test.h"

static void test_hashtable_int(void) {
  ht_t *table = ht_init(5);

  int a = 4;
  int b = 0;
  int c = 9;
  char asd[] = "asd";
  char bbb[] = "bbb";

  ht_put(table, &string_of(asd), &a);
  DEBUG_ASSERT(table->size == 1);
  ht_put(table, &string_of(bbb), &b);
  DEBUG_ASSERT(table->size == 2);
  ht_put(table, &string_of(bbb), &c);
  DEBUG_ASSERT(table->size == 2);

  // Hashtable does not free `key` param in `ht_get` so should not be heap
  // allocated
  DEBUG_ASSERT(*(int *)ht_get(table, &string_of(asd)) == 4);
  DEBUG_ASSERT(*(int *)ht_get(table, &string_of(bbb)) == 9);

  ht_free(table);
}

static void test_hashtable_string(void) {
  ht_t *table = ht_init(5);

  char asd[] = "asd";
  char qwerty[] = "qwerty";
  char qwertz[] = "qwertz";
  char qwertb[] = "qwertb";
  char longstring[] = "iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirlur";

  ht_put(table, &string_of(asd), "YOYO");
  DEBUG_ASSERT(table->size == 1);
  ht_put(table, &string_of(asd), "YAYA");
  DEBUG_ASSERT(table->size == 1);
  ht_put(table, &string_of(qwerty), "123");
  DEBUG_ASSERT(table->size == 2);
  ht_put(table, &string_of(qwertz), "BABA");
  DEBUG_ASSERT(table->size == 3);
  ht_put(table, &string_of(qwertb), "POPO");
  DEBUG_ASSERT(table->size == 4);

  DEBUG_ASSERT(strcmp(ht_get(table, &string_of(asd)), "YAYA") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, &string_of(qwerty)), "123") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, &string_of(qwertz)), "BABA") == 0);
  DEBUG_ASSERT(strcmp(ht_get(table, &string_of(qwertb)), "POPO") == 0);
  DEBUG_ASSERT(table->capacity == 10);

  ht_put(table, &string_of(longstring), "POPO");
  DEBUG_ASSERT(table->size == 5);
  ht_put(table, &string_of(""), "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfj");
  DEBUG_ASSERT(table->size == 6);
  DEBUG_ASSERT(table->capacity == 20);

  DEBUG_ASSERT(ht_get(table, &string_of("doesn't exist")) == NULL);

  ht_free(table);
}

void test_hashtable() {
  TEST_MODULE_START("hashtable");

  test_hashtable_int();
  test_hashtable_string();

  TEST_MODULE_END("hashtable");
}
