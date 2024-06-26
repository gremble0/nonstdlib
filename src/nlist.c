#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nlist.h"

/**
 * @brief Expand max capacity of a list
 *
 * @param list list to expand
 */
static void list_expand(list_t *list) {
  size_t new_size = list->capacity * 2;
  list->entries = realloc(list->entries, new_size * sizeof(list->entries));
  if (list->entries == NULL)
    err_malloc_fail();

  list->capacity = new_size;
}

/**
 * @brief Move each list element one index to the right, expands list if full
 *
 * @param list list to right shift
 */
static void list_shift_right(list_t *list) {
  if (list->size == list->capacity)
    list_expand(list);

  for (size_t i = list->size; i > 0; i--)
    list->entries[i] = list->entries[i - 1];
}

/**
 * @brief Move each list element after `from` one index to the left, element at
 * index 0 will be overwritten if `from` is 1
 *
 * @param list list to right shift
 * @param from first index to start shifting from
 */
static void list_shift_left(const list_t *list, size_t from) {
  if (from >= list->size)
    err_index_out_of_bounds(from, list->size);

  for (size_t i = from + 1; i < list->size; i++)
    list->entries[i - 1] = list->entries[i];
}

/**
 * @brief Checks if a value is present in a list.
 *
 * @param list list to check in
 * @param val value to check for
 * @return 1 if present 0 if not
 */
int list_contains(const list_t *list, const void *val) {
  for (size_t i = 0; i < list->size; ++i)
    if (list->entries[i] == val)
      return 1;

  return 0;
}

/**
 * @brief Initialize a malloc'd list with malloc'd list->values
 *
 * @param init_size initial max size of list
 * @param type_size amount of bytes used for each element in the list
 * @return a malloc'd list that should to be freed using list_free()
 */
list_t *list_init(size_t init_size) {
  list_t *list = malloc(sizeof(*list));
  if (list == NULL)
    err_malloc_fail();

  list->capacity = init_size;
  list->size = 0;
  list->entries = malloc(init_size * sizeof(*list->entries));
  if (list->entries == NULL)
    err_malloc_fail();

  return list;
}

/**
 * @brief Get a value in a list in O(1) time
 *
 * @param list list to index
 * @param index index into list
 */
void *list_get(const list_t *list, size_t index) {
  if (index >= list->size)
    err_index_out_of_bounds(index, list->size);

  return list->entries[index];
}

/**
 * @brief Pops the elemnt at the given index and returns it
 *
 * @param list list to pop from
 * @param index index of element to pop
 * @return element at the given index
 */
void *list_pop_at(list_t *list, size_t index) {
  if (index >= list->size)
    err_index_out_of_bounds(index, list->size);

  void *at_index = list->entries[index];
  list_shift_left(list, index);
  --list->size;

  return at_index;
}

/**
 * @brief Pops the last element of the list and return it
 *
 * @param list list to pop from
 * @return element at the end of the list
 */
void *list_pop_back(list_t *list) {
  if (list->size == 0)
    return NULL;

  return list->entries[--list->size];
}

/**
 * @brief Pops the first element of the list and return it
 *
 * @param list list to pop from
 * @return element at the end of the list
 */
void *list_pop_front(list_t *list) {
  if (list->size == 0)
    return NULL;

  // Save retun value before it gets overwritten by list_left_shift
  void *popped = list->entries[0];
  list_shift_left(list, 0);
  --list->size;

  return popped;
}

/**
 * @brief Remove a value from a list (only compares pointers). If value is found
 * return it and shift values after the values index to the left. If not found
 * return NULL.
 *
 * @param list list to remove from
 * @param val value to remove
 */
void *list_remove(list_t *list, void *val) {
  for (size_t i = 0; i < list->size; ++i) {
    if (list->entries[i] == val) {
      list_shift_left(list, i);
      --list->size;
      return val;
    }
  }

  return NULL;
}

/**
 * @brief Clear all values in list
 *
 * @param list list to clear
 */
void list_clear(list_t *list) {
  for (size_t i = 0; i < list->size; ++i)
    list->entries[i] = NULL;

  list->size = 0;
}

/**
 * @brief Free all variables bound to a list
 *
 * @param list list to free
 */
void list_free(list_t *list) {
  free(list->entries);
  free(list);
}

/**
 * @brief Map a function on each element in the list. For example you could map
 * free onto the list if you know all elements are heap allocated
 *
 * @param list list to map functions onto
 */
void list_map(const list_t *list, list_map_func func) {
  for (size_t i = 0; i < list->size; ++i)
    func(list->entries[i]);
}

/**
 * @brief Prints the bytes at each index in the list
 *
 * @param list list to print bytes of
 */
void list_print(const list_t *list) {
  for (size_t i = 0; i < list->size; ++i)
    printf("[%zu]: %p\n", i, list->entries[i]);
}

/**
 * @brief Push a value to the end of a list by copying the bytes in val
 *
 * @param list list to push onto
 * @param val value to push onto the list
 */
void list_push_back(list_t *list, void *val) {
  // Resize if necessary
  if (list->size == list->capacity)
    list_expand(list);

  list->entries[list->size] = val;
  ++list->size;
}

/**
 * @brief Push a value to the start of a list by shifting the rest of the list
 * to the right and copying the bytes in val to the front
 *
 * @param list list to push onto
 * @param val value to push onto the list
 */
void list_push_front(list_t *list, void *val) {
  // Resize if necessary
  if (list->size == list->capacity)
    list_expand(list);

  if (list->size > 0)
    list_shift_right(list);

  list->entries[0] = val;
  ++list->size;
}

static void list_swap(list_t *list, size_t i, size_t j) {
  void *temp = list->entries[i];
  list->entries[i] = list->entries[j];
  list->entries[j] = temp;
}

/**
 * @brief Reverse a list in-place
 *
 * @param list list to reverse
 */
void list_reverse(list_t *list) {
  for (size_t i = 0; i < list->size / 2; ++i)
    list_swap(list, i, list->size - 1 - i);
}
