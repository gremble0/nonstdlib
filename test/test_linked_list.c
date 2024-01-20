#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

void test_ll_push(void) {
    ll_t *ll = ll_init();

    ll_push(ll, "a");
    ll_push(ll, "b");
    ll_push(ll, "c");

    assert(ll->cur_size == 3);
    assert(strcmp(ll_peek(ll), "c") == 0);
    assert(strcmp(ll_seek(ll, 1), "b") == 0);
    assert(strcmp(ll_seek(ll, 2), "a") == 0);

    ll_free(ll);
    printf("\033[0;32mTests for ll_push passed\033[0;37m\n");
}

void test_ll_pop(void) {
    ll_t *ll = ll_init();

    const int a = 1;
    const int b = 2;
    const int c = 3;
    ll_push(ll, &a);
    ll_push(ll, &b);
    ll_push(ll, &c);

    assert(*(int *)ll_pop(ll) == 3);
    assert(*(int *)ll_pop(ll) == 2);
    assert(*(int *)ll_pop(ll) == 1);
    assert(ll_pop(ll) == NULL);
    assert(ll_pop(ll) == NULL);

    ll_push(ll, &a);
    assert(*(int *)ll_pop(ll) == 1);
    assert(ll_pop(ll) == NULL);

    ll_free(ll);
    printf("\033[0;32mTests for ll_pop passed\033[0;37m\n");
}

void test_linked_list(void) {
    printf("Testing stack data structure...\n");
    test_ll_push();
    test_ll_pop();
    printf("\033[0;32mAll stack data structure tests passed\033[0;37m\n");
}
