#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

void test_list_append(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_append(list, "a");
  list_append(list, "asd");
  list_append(list, "asd");
  list_append(list, "asd");
  list_append(list, "asd");
  list_append(list, "asd");

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
  list_append(list2, &a);
  list_append(list2, &b);

  assert(memcmp(&a, list_get(list2, 0), list2->type_size) == 0);
  assert(memcmp(&b, list_get(list2, 0), list2->type_size) != 0);

  assert(memcmp(&a, list_get(list2, 1), list2->type_size) != 0);
  assert(memcmp(&b, list_get(list2, 1), list2->type_size) == 0);

  list_free(list);
  printf("\033[0;32mTests for list_append passed\033[0;37m\n");
}

void test_list_clear(void) {
  list_t *list = list_init(5, sizeof(char *));

  list_append(list, "abc");
  list_append(list, "abc");
  list_append(list, "abc");
  list_append(list, "abc");
  assert(list->cur_size == 4);
  list_clear(list);
  assert(list->cur_size == 0);

  list_free(list);
  printf("\033[0;32mTests for list_clear passed\033[0;37m\n");
}

void test_list_contains(void) {
  list_t *list = list_init(5, sizeof(char *));

  const int a = 2;
  const int b = 44;

  list_append(list, &a);
  list_append(list, &b);

  assert(list_contains(list, &a) == 1);
  assert(list_contains(list, &b) == 1);

  list_free(list);
  printf("\033[0;32mTests for list_contains passed\033[0;37m\n");
}

void test_list(void) {
  printf("Testing list data structure...\n");
  test_list_append();
  test_list_clear();
  test_list_contains();
  printf("\033[0;32mAll list tests passed\033[0;37m\n");
}
