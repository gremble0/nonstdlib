#pragma once

#include <stdint.h>

// TODO: make linked list

typedef struct stack_entry {
    const void *value;
    struct stack_entry *next;
} stack_entry;

typedef struct stack {
    stack_entry *first;
    uint32_t size;
} stack;

stack *stack_init(void);
void stack_free(stack *s);
void stack_print(stack *s);
const void *stack_peek(stack *s);
const void *stack_pop(stack *s);
const void *stack_get(stack *s, uint32_t index);
void stack_push(stack *s, void *value);
