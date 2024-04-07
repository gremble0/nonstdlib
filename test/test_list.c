#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nlist.h"
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

static void test_list_expand(void) {
  list_t *list = list_init(1, sizeof(char *));

  list_push_back(list, "");
  ASSERT_TRUE(list->cur_size == 1);
  ASSERT_TRUE(list->max_size == 1);

  list_push_back(list, "");
  ASSERT_TRUE(list->cur_size == 2);
  ASSERT_TRUE(list->max_size == 2);

  list_push_back(list, "");
  ASSERT_TRUE(list->cur_size == 3);
  ASSERT_TRUE(list->max_size == 4);

  list_push_back(list, "");
  ASSERT_TRUE(list->cur_size == 4);
  ASSERT_TRUE(list->max_size == 4);

  list_push_back(list, "");
  ASSERT_TRUE(list->cur_size == 5);
  ASSERT_TRUE(list->max_size == 8);

  list_push_back(list, "");
  ASSERT_TRUE(list->cur_size == 6);
  ASSERT_TRUE(list->max_size == 8);

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
  list_t *list = list_init(5, sizeof(const int));

  const int a = 2;
  const int b = 44;
  const int c = 44;
  const int d = 42;

  list_push_back(list, &a);
  list_push_back(list, &b);

  ASSERT_TRUE(list_contains(list, &a) == 1);
  ASSERT_TRUE(list_contains(list, &b) == 1);
  ASSERT_TRUE(list_contains(list, &c) == 1);
  ASSERT_TRUE(list_contains(list, &d) == 0);

defer:
  list_free(list);
  TEST_FUNCTION_SUCCESS();
}

static void test_list_structs(void) {
  struct some_struct {
    int a;
    int b;
    int c;
    char d[15];
  };

  list_t *list = list_init(5, sizeof(struct some_struct));

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

  const struct some_struct *should_be_s2 = list_get(list, 0);
  const struct some_struct *should_be_s1 = list_get(list, 1);

  ASSERT_TRUE(should_be_s2->a == s2.a);
  ASSERT_TRUE(should_be_s1->a == s1.a);

defer:
  list_free(list);
  TEST_FUNCTION_SUCCESS();
}

void test_list(int *total_tests_ran, int *total_tests_passed) {
  TEST_MODULE_START();

  test_list_push_pop();
  test_list_expand();
  test_list_clear();
  test_list_contains();
  test_list_structs();

  TEST_MODULE_END();

  *total_tests_passed += tests_passed;
  *total_tests_ran += tests_ran;
}
