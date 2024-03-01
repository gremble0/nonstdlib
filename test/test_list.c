#include <assert.h>
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
  assert(strcmp("yoyo", yoyo) == 0);
  free(yoyo);
  // list should be: ["zozo", "xoxo"]

  char *xoxo = list_pop_back(list);
  assert(strcmp("xoxo", xoxo) == 0);
  free(xoxo);
  // list should be: ["zozo"]

  char *zozo = list_pop_back(list);
  assert(strcmp("zozo", zozo) == 0);
  free(zozo);
  // list should be: []

  assert(list_pop_front(list) == NULL);
  // list should be: []

  list_push_back(list, "yaya");
  list_push_back(list, "xaxa");
  list_push_front(list, "zaza");
  // list should be: ["zaza", "yaya", "xaxa"]

  char *xaxa = list_pop_back(list);
  assert(strcmp("xaxa", xaxa) == 0);
  free(xaxa);
  // list should be: ["zaza", "yaya"]

  char *zaza = list_pop_front(list);
  assert(strcmp("zaza", zaza) == 0);
  free(zaza);
  // list should be: ["yaya"]

  char *yaya = list_pop_back(list);
  assert(strcmp("yaya", yaya) == 0);
  free(yaya);
  // list should be: []

  assert(list_pop_front(list) == NULL);
  // list should be: []

  list_free(list);
  TEST_FUNCTION_SUCCESS("list_pop_(front & back), list_push_(front & back)");
}

static void test_list_clear(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  assert(list->cur_size == 4);
  list_clear(list);
  assert(list->cur_size == 0);

  list_free(list);
  TEST_FUNCTION_SUCCESS("list_clear");
}

static void test_list_contains(void) {
  list_t *list = list_init(5, sizeof(char *));

  const int a = 2;
  const int b = 44;

  list_push_back(list, &a);
  list_push_back(list, &b);

  assert(list_contains(list, &a) == 1);
  assert(list_contains(list, &b) == 1);

  list_free(list);
  TEST_FUNCTION_SUCCESS("list_contains");
}

void test_list(void) {
  TEST_MODULE_START("list");

  test_list_push_pop();
  test_list_clear();
  test_list_contains();

  TEST_MODULE_END("list");
}
