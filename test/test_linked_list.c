#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nerror.h"
#include "nlinked_list.h"
#include "test.h"

static void test_ll_push_back_seek(void) {
  ll_t *ll = ll_init(sizeof(char *));

  ll_push_back(ll, "a");
  ll_push_back(ll, "b");
  ll_push_back(ll, "c");
  ll_push_back(ll, "d");
  ll_push_back(ll, "e");
  ll_push_back(ll, "f");
  // ll should be: "a" -> "b" -> "c" -> "d" -> "e" -> "f"

  DEBUG_ASSERT(ll->cur_size == 6);
  DEBUG_ASSERT(strcmp(ll_peek_front(ll), "a") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 5), "f") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 2), "c") == 0);
  DEBUG_ASSERT(strcmp(ll_peek_back(ll), "f") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 1), "b") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 3), "d") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 4), "e") == 0);

  ll_free(ll);
}

static void test_ll_push_front_pop(void) {
  ll_t *ll = ll_init(sizeof(int));

  const int a = 1;
  const int b = 2;
  const int c = 3;
  ll_push_front(ll, &a);
  ll_push_front(ll, &b);
  ll_push_front(ll, &c);
  // ll should be: 3 -> 2 -> 1

  int *popped_a = ll_pop_front(ll);
  // ll should be: 2 -> 1
  int *popped_b = ll_pop_back(ll);
  // ll should be: 2
  int *popped_c = ll_pop_back(ll);
  // ll should be: (nil)

  DEBUG_ASSERT(*popped_a == 3);
  DEBUG_ASSERT(*popped_b == 1);
  DEBUG_ASSERT(*popped_c == 2);
  DEBUG_ASSERT(ll_peek_front(ll) == NULL);

  ll_push_front(ll, &a);
  // ll should be: 1

  int *popped_d = ll_pop_back(ll);
  // ll should be: (nil)

  DEBUG_ASSERT(*popped_d == 1);
  DEBUG_ASSERT(ll_peek_front(ll) == NULL);

  free(popped_a);
  free(popped_b);
  free(popped_c);
  free(popped_d);
  ll_free(ll);
}

static void test_ll_reverse(void) {
  ll_t *ll = ll_init(sizeof(char *));

  // reversing empty ll should not error
  ll_reverse(ll);

  ll_push_front(ll, "a");
  ll_push_front(ll, "b");
  ll_push_back(ll, "c");
  // ll should be: "b" -> "a" -> "c"

  ll_reverse(ll);
  // ll should be: "c" -> "a" -> "b"

  DEBUG_ASSERT(strcmp(ll_peek_front(ll), "c") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 1), "a") == 0);
  DEBUG_ASSERT(strcmp(ll_peek_back(ll), "b") == 0);

  ll_reverse(ll);
  // ll should be: "b" -> "a" -> "c"

  DEBUG_ASSERT(strcmp(ll_peek_front(ll), "b") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 1), "a") == 0);
  DEBUG_ASSERT(strcmp(ll_peek_back(ll), "c") == 0);

  ll_free(ll);
}

static void test_ll_all(void) {
  ll_t *ll = ll_init(sizeof(char *));

  ll_push_front(ll, "a");
  ll_push_front(ll, "b");
  ll_push_back(ll, "c");
  // ll should be: "b" -> "a" -> "c"

  DEBUG_ASSERT(ll->cur_size == 3);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 2), "c") == 0);
  DEBUG_ASSERT(strcmp(ll_peek_front(ll), "b") == 0);

  free(ll_pop_back(ll));
  // ll should be: "b" -> "a"
  DEBUG_ASSERT(strcmp(ll_peek_front(ll), "b") == 0);
  DEBUG_ASSERT(strcmp(ll_seek(ll, 1), "a") == 0);

  free(ll_pop_back(ll));
  // ll should be: "b"
  DEBUG_ASSERT(strcmp(ll_peek_front(ll), "b") == 0);

  free(ll_pop_back(ll));
  // ll should be: (nil)
  DEBUG_ASSERT(ll_peek_front(ll) == NULL);

  ll_free(ll);
}

void test_linked_list() {
  TEST_MODULE_START("linked list");

  test_ll_push_back_seek();
  test_ll_push_front_pop();
  test_ll_reverse();
  test_ll_all();

  TEST_MODULE_END("linked list");
}
