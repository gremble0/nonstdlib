#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

/**
 * @brief Appends a value to the end of a linked list (index ll->cur_size - 1).
 *        Mallocs and copies ll->type_size bytes from value into the linked list
 *        entries value
 *
 * @param ll linked list to append onto
 * @param value value to append
 */
void ll_append(ll_t *ll, const void *value) {
    ll_entry_t *new = malloc(sizeof(ll_entry_t));
    new->value = malloc(ll->type_size);
    memcpy(new->value, value, ll->type_size);
    new->next = NULL;

    ll_entry_t *iter = ll->first;
    if (iter == NULL) {
        ll->first = new;
        ++ll->cur_size;
        return;
    }

    while (iter->next != NULL) {
        iter = iter->next;
    }

    iter->next = new;
    ++ll->cur_size;
}

/**
 * @brief Initializes an empty linked list
 *
 * @return an empty linked list
 */
ll_t *ll_init(size_t type_size) {
    ll_t *ll = malloc(sizeof(ll_t));
    ll->cur_size = 0;
    ll->type_size = type_size;
    ll->first = NULL;

    return ll;
}

/**
 * @brief Frees memory allocated for a linked list and all its entries
 *
 * @param s linked list to free allocated memory for
 */
void ll_free(ll_t *ll) {
    if (ll->cur_size == 0) {
        free(ll);
        return;
    }

    ll_entry_t *entry = ll->first;
    while (entry->next != NULL) {
        ll_entry_t *next = entry->next;
        free(entry->value);
        free(entry);
        entry = next;
    }

    free(ll);
}

/**
 * @brief Get the first element in the linked list without modifying it
 *
 * @param s linked list to get element from
 */
void *ll_peek(ll_t *ll) {
    return ll->first->value;
}

/**
 * @brief Pops first entry off the linked list and returns it. Returned value
 *        needs to be freed
 *
 * @param s linked list to pop from
 */
void *ll_pop(ll_t *ll) {
    if (ll->cur_size == 0) {
        return NULL;
    }

    ll_entry_t *popped = ll->first;
    void *ret = popped->value;
    ll->first = popped->next;
    --ll->cur_size;

    free(popped);
    return ret;
}

/**
 * @brief Prints contents of given stack to stdout
 *
 * @param s stack to get contents from
 */
void ll_print(ll_t *ll) {
    ll_entry_t *entry = ll->first;
    if (ll->first == NULL) {
        printf("--empty linked list--\n");
        return;
    }

    int index = 0;
    while (entry != NULL) {
        printf("[%u]: %p ->\n", index++, entry->value);
        entry = entry->next;
    }
}

/**
 * @brief Gets value at index into linked list in O(n) time complexity
 *
 * @param s linked list to get value from
 * @param index how far into the linked list to seek
 */
void *ll_seek(ll_t *ll, int index) {
    ll_entry_t *entry = ll->first;
    while (index-- > 0) {
        entry = entry->next;
    }

    return entry->value;
}

/**
 * @brief Pushes an entry onto the front of the linked list (index 0). 
 *        Mallocs and copies ll->type_size bytes from value into the
 *        linked list entries value
 *
 * @param s linked list to push into
 * @param value what to push onto the linked list
 */
void ll_push(ll_t *ll, const void *value) {
    ll_entry_t *new = malloc(sizeof(ll_entry_t));
    new->value = malloc(ll->type_size);
    memcpy(new->value, value, ll->type_size);
    new->next = ll->first;
    ll->first = new;
    ++ll->cur_size;
}
