#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nlinked_list.h"

/**
 * @brief Initializes an empty linked list
 *
 * @return an empty linked list
 */
ll_t *ll_init(size_t type_size) {
  ll_t *ll = malloc(sizeof(*ll));
  if (ll == NULL)
    err_malloc_fail();

  ll->cur_size = 0;
  ll->type_size = type_size;
  ll->first = NULL;
  ll->last = NULL;

  return ll;
}

/**
 * @brief Get the last element in the linked list without modifying it
 *
 * @param s linked list to peek into
 */
void *ll_peek_back(ll_t *ll) {
  if (ll->last == NULL)
    return NULL;

  return ll->last->value;
}

/**
 * @brief Get the first element in the linked list without modifying it.
 *
 * @param s linked list to peek into
 */
void *ll_peek_front(ll_t *ll) {
  if (ll->first == NULL)
    return NULL;

  return ll->first->value;
}

/**
 * @brief Removes last entry in the linked list and returns it.
 *
 * @param s linked list to pop from
 */
void *ll_pop_back(ll_t *ll) {
  if (ll->last == NULL)
    err_pop_from_empty_list();

  ll_entry_t *popped = ll->last;
  void *ret = popped->value;

  ll->last = popped->prev;
  if (ll->last == NULL)
    ll->first = NULL;
  else
    ll->last->next = NULL;

  --ll->cur_size;
  free(popped);

  return ret;
}

/**
 * @brief Pops first entry in the linked list and returns it.
 *
 * @param s linked list to pop from
 */
void *ll_pop_front(ll_t *ll) {
  if (ll->first == NULL)
    err_pop_from_empty_list();

  ll_entry_t *popped = ll->first;
  void *ret = popped->value;

  ll->first = popped->next;
  if (ll->first == NULL)
    ll->last = NULL;
  else
    ll->first->prev = NULL;

  --ll->cur_size;
  free(popped);

  return ret;
}

/**
 * @brief Gets value at index into linked list in O(n) time complexity
 *
 * @param s linked list to get value from
 * @param index how far into the linked list to seek
 */
void *ll_seek(ll_t *ll, size_t index) {
  // Index out of bounds
  if (index >= ll->cur_size)
    return NULL;

  // Seek front to back if index is small, back to front if index is large
  if (index <= ll->cur_size / 2) {
    ll_entry_t *entry = ll->first;
    while (index-- > 0)
      entry = entry->next;

    return entry->value;
  } else {
    index = ll->cur_size - index;
    ll_entry_t *entry = ll->last;
    while (--index > 0)
      entry = entry->prev;

    return entry->value;
  }
}

/**
 * @brief Frees memory allocated for a linked list, all its entries and all its
 * entries' values
 *
 * @param s linked list to free allocated memory for
 */
void ll_free(ll_t *ll) {
  ll_entry_t *entry = ll->first;
  while (entry != NULL) {
    ll_entry_t *next = entry->next;
    free(entry);
    entry = next;
  }

  free(ll);
}

/**
 * @brief Prints contents of given stack to stdout
 *
 * @param s stack to get contents from
 */
void ll_print(ll_t *ll) {
  ll_entry_t *entry = ll->first;
  if (entry == NULL) {
    printf("--empty linked list--\n");
    return;
  }

  int index = 0;
  while (entry != NULL) {
    printf("[%u]: %p ->, prev -> %p, next -> %p\n", index++, entry, entry->prev,
           entry->next);
    entry = entry->next;
  }
}

/**
 * @brief Pushes a value to the end of a linked list (after ll->last).
 *
 * @param ll linked list to push onto
 * @param value what to push
 */
void ll_push_back(ll_t *ll, void *value) {
  ll_entry_t *new = malloc(sizeof(*ll));
  if (new == NULL)
    err_malloc_fail();

  new->value = value;
  new->prev = ll->last;
  new->next = NULL;

  // Update pointers in ll
  if (ll->last == NULL)
    ll->first = new;
  else
    ll->last->next = new;

  ll->last = new;
  ++ll->cur_size;
}

/**
 * @brief Pushes an entry onto the front of the linked list (before ll->first).
 *
 * @param ll linked list to push onto
 * @param value what to push
 */
void ll_push_front(ll_t *ll, void *value) {
  ll_entry_t *new = malloc(sizeof(*new));
  if (new == NULL)
    err_malloc_fail();

  new->value = value;
  new->prev = NULL;
  new->next = ll->first;

  // Update pointers in ll
  if (ll->last == NULL)
    ll->last = new;
  else
    ll->first->prev = new;

  ll->first = new;
  ++ll->cur_size;
}

/**
 * @brief Reverse a linked list in place
 *
 * @param ll linked list to reverse
 */
void ll_reverse(ll_t *ll) {
  if (ll->first == NULL)
    return;

  // Update first/last
  ll_entry_t *first = ll->first;

  ll->first = ll->last;
  ll->first->next = ll->first->prev;
  ll->first->prev = NULL;

  ll->last = first;
  ll->last->prev = ll->last->next;
  ll->last->next = NULL;

  // Update all other entries.
  // entry is now the same as ll->last->prev before previous swaps
  ll_entry_t *entry = ll->first->next;
  while (entry->next != NULL) {
    ll_entry_t *prev = entry->prev;
    entry->prev = entry->next;
    entry->next = prev;

    entry = prev;
  }
}
