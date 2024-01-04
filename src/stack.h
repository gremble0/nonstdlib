#pragma once

#include <stdint.h>

typedef struct stack_entry {
    void *value;
    struct stack_entry *next;
} stack_entry;

typedef struct stack {
    stack_entry *first;
    uint32_t size;
} stack;

stack *stack_init(void);
void   stack_free(stack *s);
void   stack_print(stack *s);
void  *stack_pop(stack *s);
void  *stack_get(stack *s, uint32_t index);
void   stack_push(stack *s, void *value);
