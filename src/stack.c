#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

/**
 * @brief Initialiazes an empty stack data structure
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
 * @brief Frees memory allocated for a stack and all its entries
 *
 * @param s stack to free allocated memory for
 */
void stack_free(stack *s) {
    if (s->size == 0) {
        free(s);
        return;
    }

    stack_entry *entry = s->first;
    while (entry->next != NULL) {
        stack_entry *next = entry->next;
        free((char*)entry->value);
        free(entry);
        entry = next;
    }

    free(s);
}

/**
 * @brief Prints contents of given stack to stdout
 *
 * @param s stack to get contents from
 */
void stack_print(stack *s) {
    stack_entry *entry = s->first;
    if (s->size == 0) {
        printf("--empty stack--\n");
        return;
    }

    uint32_t index = 0;
    while (entry != NULL) {
        printf("[%u]: %p\n", index++, entry->value);
        entry = entry->next;
    }
}

/**
 * @brief Pops first entry off the stack and returns it. Returned value needs
 *        to be freed
 *
 * @param s stack to pop from
 */
const void *stack_pop(stack *s) {
    if (s->size == 0) {
        return NULL;
    }

    stack_entry *popped = s->first;
    const void *ret = popped->value;
    s->first = popped->next;
    --s->size;
    free(popped);
    return ret;
}

/**
 * @brief Gets an entry at the given index into a stack
 *
 * @param s stack to get entry from
 * @param index index into stack to get entry at
 */
const void *stack_get(stack *s, uint32_t index) {
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
 * @brief Pushes an entry onto the front of the stack
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
