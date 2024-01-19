#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

/**
 * @brief Initializes an empty linked list
 *
 * @return an empty linked list
 */
ll_t *ll_init(void) {
    ll_t *ll = malloc(sizeof(ll_t));
    ll->size = 0;
    ll->first = NULL;

    return ll;
}

/**
 * @brief Frees memory allocated for a linked list and all its entries
 *
 * @param s linked list to free allocated memory for
 */
void ll_free(ll_t *ll) {
    if (ll->size == 0) {
        free(ll);
        return;
    }

    ll_entry_t *entry = ll->first;
    while (entry->next != NULL) {
        ll_entry_t *next = entry->next;
        free((char*)entry->value);
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
const void *ll_peek(ll_t *ll) {
    return ll->first->value;
}

/**
 * @brief Pops first entry off the linked list and returns it. Returned value
 *        needs to be freed
 *
 * @param s linked list to pop from
 */
const void *ll_pop(ll_t *ll) {
    if (ll->size == 0) {
        return NULL;
    }

    ll_entry_t *popped = ll->first;
    const void *ret = popped->value;
    ll->first = popped->next;
    --ll->size;
    free(popped);
    return ret;
}

/**
 * @brief Gets value at index into linked list in O(n) time complexity
 *
 * @param s linked list to get value from
 * @param index how far into the linked list to seek
 */
const void *ll_seek(ll_t *ll, int index) {
    ll_entry_t *entry = ll->first;
    while (index-- > 0) {
        entry = entry->next;
    }

    return entry->value;
}

/**
 * @brief Pushes an entry onto the front of the linked list
 *
 * @param s linked list to push into
 * @param value what to push onto the linked list, needs to be malloc'd beforehand
 */
void ll_append(ll_t *ll, void *value) {
    ll_entry_t *new_entry = malloc(sizeof(ll_entry_t));
    new_entry->value = value;
    new_entry->next = ll->first;
    ll->first = new_entry;
    ++ll->size;
}
