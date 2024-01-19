#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

void test_linked_list(void) {
    printf("Testing stack data structure...\n");

    ll_t *ll = ll_init();

    int *val1 = malloc(sizeof(int));
    int *val2 = malloc(sizeof(int));
    int *val3 = malloc(sizeof(int));
    *val1 = 1;
    *val2 = 2;
    *val3 = 3;
    ll_push(ll, val1);
    ll_push(ll, val2);
    ll_push(ll, val3);

    assert(ll->size == 3);
    assert(*(int *)ll_seek(ll, 0) == 3);
    assert(*(int *)ll_seek(ll, 1) == 2);
    assert(*(int *)ll_seek(ll, 2) == 1);

    const int *popped1 = ll_pop(ll);
    const int *popped2 = ll_pop(ll);
    const int *popped3 = ll_pop(ll);

    assert(ll->size == 0);
    assert(*popped1 == 3);
    assert(*popped2 == 2);
    assert(*popped3 == 1);

    assert(popped3 == val1);
    assert(popped2 == val2);
    assert(popped1 == val3);
    assert(ll_pop(ll) == NULL);

    free(val1);
    free(val2);
    free(val3);

    char *val4 = malloc(sizeof(char));
    long long *val5 = malloc(sizeof(long long));
    *val4 = 't';
    *val5 = 1000;
    ll_push(ll, val4);
    ll_push(ll, val5);
    
    assert(*(long long *)ll_peek(ll) == 1000);
    assert(*(long long *)ll_pop(ll) == 1000);
    assert(*(char *)ll_peek(ll) == 't');
    assert(*(char *)ll_pop(ll) == 't');

    assert(ll->size == 0);
    int *val6 = malloc(sizeof(int));
    *val6 = 2;
    ll_append(ll, val6);
    assert(*(int *)ll_seek(ll, ll->size - 1) == 2);

    free(val4);
    free(val5);
    ll_free(ll);

    printf("\033[0;32mAll stack data structure tests passed\033[0;37m\n");
}
