#include <assert.h>
#include <stdio.h>
#include <string.h>

// TODO: TEST_SUCCESS(test_name) macro
// TODO: custom assert that actually says what is different if different
#include "list.h"

void test_list_push_back(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_back(list, "a");
  list_push_back(list, "asd");
  list_push_back(list, "asd");
  list_push_back(list, "asd");
  list_push_back(list, "asd");
  list_push_back(list, "asd");

  assert(list->cur_size == 6);
  assert(memcmp("a", list_get(list, 0), list->type_size) == 0);
  assert(memcmp("b", list_get(list, 0), list->type_size) != 0);
  assert(memcmp("asd", list_get(list, 0), list->type_size) != 0);

  assert(memcmp("asd", list_get(list, 1), list->type_size) == 0);
  assert(memcmp("asd", list_get(list, 2), list->type_size) == 0);
  assert(memcmp("asd", list_get(list, 3), list->type_size) == 0);

  list_t *list2 = list_init(10, sizeof(int));
  const int a = 2;
  const int b = 44;
  list_push_back(list2, &a);
  list_push_back(list2, &b);

  assert(memcmp(&a, list_get(list2, 0), list2->type_size) == 0);
  assert(memcmp(&b, list_get(list2, 0), list2->type_size) != 0);

  assert(memcmp(&a, list_get(list2, 1), list2->type_size) != 0);
  assert(memcmp(&b, list_get(list2, 1), list2->type_size) == 0);

  list_free(list);
  printf("\033[0;32mTest for list_append passed\033[0;37m\n");
}

void test_list_push_front(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_front(list, "yoyo");
  list_push_front(list, "xoxo");
  list_push_front(list, "zozo");

  assert(strcmp("zozo", list_get(list, 0)) == 0);
  assert(strcmp("xoxo", list_get(list, 1)) == 0);
  assert(strcmp("yoyo", list_get(list, 2)) == 0);

  list_free(list);
  printf("\033[0;32mTest for list_push_front passed\033[0;37m\n");
}

void test_list_pop(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_front(list, "yoyo");
  list_push_front(list, "xoxo");
  list_push_front(list, "zozo");
  // list should be: ["zozo", "xoxo", "yoyo"]

  assert(strcmp("yoyo", list_pop_back(list)) == 0);
  // list should be: ["zozo", "xoxo"]

  assert(strcmp("xoxo", list_pop_back(list)) == 0);
  // list should be: ["zozo"]

  assert(strcmp("zozo", list_pop_back(list)) == 0);
  // list should be: []

  assert(list_pop_front(list) == NULL);
  // list should be: []

  list_push_back(list, "yaya");
  list_push_back(list, "xaxa");
  list_push_front(list, "zaza");
  // list should be: ["zaza", "yaya", "xaxa"]

  assert(strcmp("xaxa", list_pop_back(list)) == 0);
  // list should be: ["zaza", "yaya"]

  assert(strcmp("zaza", list_pop_front(list)) == 0);
  // list should be: ["yaya"]

  assert(strcmp("yaya", list_pop_back(list)) == 0);
  // list should be: []

  assert(list_pop_front(list) == NULL);
  // list should be: []

  list_free(list);
  printf("\033[0;32mTest for list_pop_(front & back) passed\033[0;37m\n");
}

void test_list_clear(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  list_push_back(list, "abc");
  assert(list->cur_size == 4);
  list_clear(list);
  assert(list->cur_size == 0);

  list_free(list);
  printf("\033[0;32mTest for list_clear passed\033[0;37m\n");
}

void test_list_contains(void) {
  list_t *list = list_init(5, sizeof(char *));

  const int a = 2;
  const int b = 44;

  list_push_back(list, &a);
  list_push_back(list, &b);

  assert(list_contains(list, &a) == 1);
  assert(list_contains(list, &b) == 1);

  list_free(list);
  printf("\033[0;32mTest for list_contains passed\033[0;37m\n");
}

void test_list(void) {
  printf("Testing list data structure...\n");
  test_list_push_back();
  test_list_push_front();
  test_list_clear();
  test_list_contains();
  test_list_pop();
  printf("\033[0;32mAll list tests passed\033[0;37m\n");
}
