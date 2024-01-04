#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

void test_stack(void) {
    printf("Testing stack data structure...\n");
    stack *s = stack_init();

    uint32_t *val1 = malloc(sizeof(uint32_t));
    uint32_t *val2 = malloc(sizeof(uint32_t));
    uint32_t *val3 = malloc(sizeof(uint32_t));
    *val1 = 1;
    *val2 = 2;
    *val3 = 3;
    stack_push(s, val1);
    stack_push(s, val2);
    stack_push(s, val3);

    assert(s->size == 3);
    assert(*(uint32_t *)stack_get(s, 0) == 3);
    assert(*(uint32_t *)stack_get(s, 1) == 2);
    assert(*(uint32_t *)stack_get(s, 2) == 1);

    uint32_t *popped1 = stack_pop(s);
    uint32_t *popped2 = stack_pop(s);
    uint32_t *popped3 = stack_pop(s);

    assert(s->size == 0);
    assert(*popped1 == 3);
    assert(*popped2 == 2);
    assert(*popped3 == 1);

    assert(popped3 == val1);
    assert(popped2 == val2);
    assert(popped1 == val3);
    assert(stack_pop(s) == NULL);

    free(val1);
    free(val2);
    free(val3);

    char *val4 = malloc(sizeof(char));
    uint64_t *val5 = malloc(sizeof(uint64_t));
    *val4 = 't';
    *val5 = 1000;
    stack_push(s, val4);
    stack_push(s, val5);
    
    assert(*(uint64_t *)stack_pop(s) == 1000);
    assert(*(char *)stack_pop(s) == 't');

    free(val4);
    free(val5);
    stack_free(s);

    printf("\033[0;32mAll stack data structure tests passed\033[0;37m\n");
}

