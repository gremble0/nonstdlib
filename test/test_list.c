#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nerror.h"
#include "nlist.h"
#include "test.h"

static void test_list_push_pop(void) {
  list_t *list = list_init(5);

  char *yoyo = "yoyo";
  char *xoxo = "xoxo";
  char *zozo = "zozo";

  list_push_front(list, yoyo);
  list_push_front(list, xoxo);
  list_push_front(list, zozo);
  // list should be: ["zozo", "xoxo", "yoyo"]

  DEBUG_ASSERT(yoyo == list_pop_back(list) && strcmp(yoyo, "yoyo") == 0);
  // list should be: ["zozo", "xoxo"]

  DEBUG_ASSERT(xoxo == list_pop_back(list) && strcmp(xoxo, "xoxo") == 0);
  // list should be: ["zozo"]

  DEBUG_ASSERT(zozo == list_pop_back(list) && strcmp(zozo, "zozo") == 0);
  // list should be: []

  DEBUG_ASSERT(list_pop_front(list) == NULL);
  // list should be: []

  list_push_back(list, yoyo);
  list_push_back(list, xoxo);
  list_push_front(list, zozo);
  // list should be: ["zozo", "yoyo", "xoxo"]

  DEBUG_ASSERT(xoxo == list_pop_back(list) && strcmp(xoxo, "xoxo") == 0);
  // list should be: ["zozo", "yoyo"]

  list_push_front(list, "lololololololoo very long long long string :)))))");
  // list should be: ["zozo", "yoyo", "lololololololoo very long long long
  // string :)))))"]

  DEBUG_ASSERT(strcmp(list_pop_front(list),
                      "lololololololoo very long long long string :)))))") ==
               0);

  DEBUG_ASSERT(yoyo == list_pop_back(list) && strcmp(yoyo, "yoyo") == 0);
  // list should be: ["zozo"]

  DEBUG_ASSERT(zozo == list_pop_back(list) && strcmp(zozo, "zozo") == 0);
  // list should be: []

  DEBUG_ASSERT(list_pop_front(list) == NULL);
  // list should be: []

  list_free(list);
}

static void test_list_expand(void) {
  list_t *list = list_init(1);

  list_push_back(list, "");
  DEBUG_ASSERT(list->cur_size == 1);
  DEBUG_ASSERT(list->max_size == 1);

  list_push_back(list, "");
  DEBUG_ASSERT(list->cur_size == 2);
  DEBUG_ASSERT(list->max_size == 2);

  list_push_back(list, "");
  DEBUG_ASSERT(list->cur_size == 3);
  DEBUG_ASSERT(list->max_size == 4);

  list_push_back(list, "");
  DEBUG_ASSERT(list->cur_size == 4);
  DEBUG_ASSERT(list->max_size == 4);

  list_push_back(list, "");
  DEBUG_ASSERT(list->cur_size == 5);
  DEBUG_ASSERT(list->max_size == 8);

  list_push_back(list, "");
  DEBUG_ASSERT(list->cur_size == 6);
  DEBUG_ASSERT(list->max_size == 8);

  list_free(list);
}

static void test_list_clear(void) {
  list_t *list = list_init(5);

  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  DEBUG_ASSERT(list->cur_size == 4);
  list_clear(list);
  DEBUG_ASSERT(list->cur_size == 0);

  list_free(list);
}

static void test_list_contains(void) {
  list_t *list = list_init(5);

  int a = 1;
  int b = 2;
  int c = 2;
  int d = 42;

  list_push_back(list, &a);
  list_push_back(list, &b);

  DEBUG_ASSERT(list_contains(list, &a) == 1);
  DEBUG_ASSERT(list_contains(list, &b) == 1);
  DEBUG_ASSERT(list_contains(list, &c) == 0);
  DEBUG_ASSERT(list_contains(list, &d) == 0);

  list_free(list);
}

static void test_list_structs(void) {
  struct some_struct {
    int a;
    int b;
    int c;
    char d[15];
  };

  list_t *list = list_init(5);

  struct some_struct s1 = {
      10,
      20,
      30,
      "hello",
  };
  struct some_struct s2 = {
      1,
      2,
      3,
      "nonstdlib",
  };
  list_push_back(list, &s1);
  list_push_front(list, &s2);

  struct some_struct *should_be_s2 = list_get(list, 0);
  struct some_struct *should_be_s1 = list_get(list, 1);

  DEBUG_ASSERT(should_be_s2 == &s2);
  DEBUG_ASSERT(should_be_s1 == &s1);

  list_free(list);
}

void test_list() {
  TEST_MODULE_START("list");

  test_list_push_pop();
  test_list_expand();
  test_list_clear();
  test_list_contains();
  test_list_structs();

  TEST_MODULE_END("list");
}
