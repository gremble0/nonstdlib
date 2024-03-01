#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TODO: custom assert that actually says what is different if different

#include "list.h"
#include "test.h"

static int tests_passed = 0;
static int tests_ran = 0;

static void test_list_push_pop(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_front(list, "yoyo");
  list_push_front(list, "xoxo");
  list_push_front(list, "zozo");
  // list should be: ["zozo", "xoxo", "yoyo"]

  char *yoyo = list_pop_back(list);
  ASSERT_TRUE(strcmp("yoyo", yoyo) == 0);
  free(yoyo);
  // list should be: ["zozo", "xoxo"]

  char *xoxo = list_pop_back(list);
  ASSERT_TRUE(strcmp("xoxo", xoxo) == 0);
  free(xoxo);
  // list should be: ["zozo"]

  char *zozo = list_pop_back(list);
  ASSERT_TRUE(strcmp("zozo", zozo) == 0);
  free(zozo);
  // list should be: []

  ASSERT_TRUE(list_pop_front(list) == NULL);
  // list should be: []

  list_push_back(list, "yaya");
  list_push_back(list, "xaxa");
  list_push_front(list, "zaza");
  // list should be: ["zaza", "yaya", "xaxa"]

  char *xaxa = list_pop_back(list);
  ASSERT_TRUE(strcmp("xaxa", xaxa) == 0);
  free(xaxa);
  // list should be: ["zaza", "yaya"]

  char *zaza = list_pop_front(list);
  ASSERT_TRUE(strcmp("zaza", zaza) == 0);
  free(zaza);
  // list should be: ["yaya"]

  char *yaya = list_pop_back(list);
  ASSERT_TRUE(strcmp("yaya", yaya) == 0);
  free(yaya);
  // list should be: []

  ASSERT_TRUE(list_pop_front(list) == NULL);
  // list should be: []

defer:
  list_free(list);
  TEST_FUNCTION_SUCCESS();
}

static void test_list_clear(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  ASSERT_TRUE(list->cur_size == 4);
  list_clear(list);
  ASSERT_TRUE(list->cur_size == 0);

defer:
  list_free(list);
  TEST_FUNCTION_SUCCESS();
}

static void test_list_contains(void) {
  list_t *list = list_init(5, sizeof(char *));

  const int a = 2;
  const int b = 44;

  list_push_back(list, &a);
  list_push_back(list, &b);

  ASSERT_TRUE(list_contains(list, &a) == 1);
  ASSERT_TRUE(list_contains(list, &b) == 1);

defer:
  list_free(list);
  TEST_FUNCTION_SUCCESS();
}

void test_list(void) {
  TEST_MODULE_START();

  test_list_push_pop();
  test_list_clear();
  test_list_contains();

  TEST_MODULE_END();
}
