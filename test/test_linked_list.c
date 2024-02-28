#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

void test_ll_push_back_seek(void) {
  ll_t *ll = ll_init(sizeof(char *));

  ll_push_back(ll, "a");
  ll_push_back(ll, "b");
  ll_push_back(ll, "c");
  ll_push_back(ll, "d");
  ll_push_back(ll, "e");
  ll_push_back(ll, "f");
  // ll should be: "a" -> "b" -> "c" -> "d" -> "e" -> "f"

  // order of peeking and seeking should not matter
  assert(ll->cur_size == 6);
  assert(strcmp(ll_peek_front(ll), "a") == 0);
  assert(strcmp(ll_seek(ll, 5), "f") == 0);
  assert(strcmp(ll_seek(ll, 2), "c") == 0);
  assert(strcmp(ll_peek_back(ll), "f") == 0);
  assert(strcmp(ll_seek(ll, 1), "b") == 0);
  assert(strcmp(ll_seek(ll, 3), "d") == 0);
  assert(strcmp(ll_seek(ll, 4), "e") == 0);

  ll_free(ll);
  printf("\033[0;32mTests for ll_push_back, ll_seek, ll_peek(front & back) "
         "passed\033[0;37m\n");
}

void test_ll_push_front_pop(void) {
  ll_t *ll = ll_init(sizeof(int));

  const int a = 1;
  const int b = 2;
  const int c = 3;
  ll_push_front(ll, &a);
  ll_push_front(ll, &b);
  ll_push_front(ll, &c);
  // ll should be: 3 -> 2 -> 1

  assert(*(int *)ll_pop_front(ll) == 3);
  // ll should be: 2 -> 1
  assert(*(int *)ll_pop_back(ll) == 1);
  // ll should be: 2
  assert(*(int *)ll_pop_back(ll) == 2);
  // ll should be: (nil)
  assert(ll_pop_back(ll) == NULL);
  ll_push_front(ll, &a);
  // ll should be: 1
  assert(*(int *)ll_pop_back(ll) == 1);
  // ll should be: (nil)
  assert(ll_pop_back(ll) == NULL);

  ll_free(ll);
  printf("\033[0;32mTests for ll_push_front and ll_pop_(front & back) "
         "passed\033[0;37m\n");
}

void test_ll_reverse(void) {
  ll_t *ll = ll_init(sizeof(char *));

  // reversing empty ll should not error
  ll_reverse(ll);

  ll_push_front(ll, "a");
  ll_push_front(ll, "b");
  ll_push_back(ll, "c");
  // ll should be: "b" -> "a" -> "c"

  ll_reverse(ll);
  // ll should be: "c" -> "a" -> "b"

  assert(strcmp(ll_peek_front(ll), "c") == 0);
  assert(strcmp(ll_seek(ll, 1), "a") == 0);
  assert(strcmp(ll_peek_back(ll), "b") == 0);

  ll_free(ll);
  printf("\033[0;32mTests for ll_reverse passed\033[0;37m\n");
}

void test_ll_all(void) {
  ll_t *ll = ll_init(sizeof(char *));

  ll_push_front(ll, "a");
  ll_push_front(ll, "b");
  ll_push_back(ll, "c");
  // ll should be: "b" -> "a" -> "c"

  assert(ll->cur_size == 3);
  assert(strcmp(ll_seek(ll, 2), "c") == 0);
  assert(strcmp(ll_peek_front(ll), "b") == 0);

  ll_pop_back(ll);
  // ll should be: "b" -> "a"
  assert(strcmp(ll_peek_front(ll), "b") == 0);
  assert(strcmp(ll_seek(ll, 1), "a") == 0);
  ll_pop_back(ll);
  // ll should be: "b"
  assert(strcmp(ll_peek_front(ll), "b") == 0);
  ll_pop_back(ll);
  // ll should be: (nil)
  assert(ll_peek_front(ll) == NULL);

  ll_free(ll);
  printf("\033[0;32mTests for mix of all linked list functions "
         "passed\033[0;37m\n");
}

void test_linked_list(void) {
  printf("Testing linked list...\n");
  test_ll_push_back_seek();
  test_ll_push_front_pop();
  test_ll_reverse();
  test_ll_all();
  printf("\033[0;32mAll linked list tests passed\033[0;37m\n");
}
