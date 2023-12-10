#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/**
 * Initialiazes an empty stack data structure
 *
 * @return an empty stack
 */
stack *stack_init(void) {
    stack *new_stack = malloc(sizeof(stack));
    new_stack->size = 0;
    new_stack->first = NULL;

    return new_stack;
}

/**
 * Frees memory allocated for a stack and all its entries
 *
 * @param s stack to free allocated memory for
 */
void stack_free(stack *s) {
    stack_entry *entry = s->first;
    while (entry->next != NULL) {
        stack_entry *next = entry->next;
        free(entry);
        free(entry->value);
        entry = next;
    }

    free(entry);
    free(s);
}

/**
 * Pops first entry off the stack and returns it
 *
 * @param s stack to pop from
 */
void *stack_pop(stack *s) {
    if (s->size == 0) {
        return NULL;
    }
    stack_entry *popped = s->first;
    s->first = s->first->next;
    --s->size;
    return popped;
}

/**
 * Gets an entry at the given index into a stack
 *
 * @param s stack to get entry from
 * @param index index into stack to get entry at
 */
void *stack_get(stack *s, uint32_t index) {
    if (index >= s->size) {
        fprintf(stderr, "stack_get(): index %u out of bounds", index);
        return NULL;
    }

    stack_entry *entry = s->first;
    while (index-- > 0) {
        entry = entry->next;
    }

    return entry->value;
}

/**
 * Pushes an entry onto the front of the stack
 *
 * @param s stack to push into
 * @param value what to push onto the stack, needs to be malloc'd beforehand
 */
void stack_push(stack *s, void *value) {
    stack_entry *new_entry = malloc(sizeof(stack_entry));
    new_entry->value = value;
    new_entry->next = s->first;
    s->first = new_entry;
    ++s->size;
}
