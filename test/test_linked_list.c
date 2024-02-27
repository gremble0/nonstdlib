#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

void test_ll_append_seek(void) {
  ll_t *ll = ll_init(sizeof(char *));

  ll_append(ll, "a");
  ll_append(ll, "b");
  ll_append(ll, "c");
  ll_append(ll, "d");
  ll_append(ll, "e");
  ll_append(ll, "f");

  assert(ll->cur_size == 6);
  assert(strcmp(ll_peek(ll), "a") == 0);
  assert(strcmp(ll_seek(ll, 1), "b") == 0);
  assert(strcmp(ll_seek(ll, 2), "c") == 0);
  assert(strcmp(ll_seek(ll, 3), "d") == 0);
  assert(strcmp(ll_seek(ll, 4), "e") == 0);
  assert(strcmp(ll_seek(ll, 5), "f") == 0);

  ll_free(ll);
  printf("\033[0;32mTests for ll_append and ll_seek passed\033[0;37m\n");
}

void test_ll_push_pop(void) {
  ll_t *ll = ll_init(sizeof(int));

  const int a = 1;
  const int b = 2;
  const int c = 3;
  ll_push(ll, &a);
  ll_push(ll, &b);
  ll_push(ll, &c);

  // printf("%d\n", *(int *)ll_seek(ll, 0));
  // printf("%d\n", *(int *)ll_seek(ll, 1));
  // printf("%d\n", *(int *)ll_seek(ll, 2));
  assert(*(int *)ll_pop(ll) == 1);
  assert(*(int *)ll_pop(ll) == 2);
  assert(*(int *)ll_pop(ll) == 3);
  assert(ll_pop(ll) == NULL);

  ll_push(ll, &a);
  assert(*(int *)ll_pop(ll) == 1);
  assert(ll_pop(ll) == NULL);

  ll_free(ll);
  printf("\033[0;32mTests for ll_push and ll_pop passed\033[0;37m\n");
}

// TODO: remove?
void test_ll_peek(void) {
  ll_t *ll = ll_init(sizeof(char *));

  ll_push(ll, "a");
  ll_push(ll, "b");
  ll_push(ll, "c");

  assert(ll->cur_size == 3);
  assert(strcmp(ll_peek(ll), "c") == 0);
  ll_pop(ll);
  assert(strcmp(ll_peek(ll), "b") == 0);
  ll_pop(ll);
  assert(strcmp(ll_peek(ll), "a") == 0);
  ll_pop(ll);
  assert(ll_peek(ll) == NULL);

  ll_free(ll);
  printf("\033[0;32mTests for ll_push passed\033[0;37m\n");
}

void test_linked_list(void) {
  printf("Testing linked list...\n");
  test_ll_append_seek();
  test_ll_push_pop();
  test_ll_peek();
  printf("\033[0;32mAll linked list tests passed\033[0;37m\n");
}
