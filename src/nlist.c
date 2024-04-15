#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nerror.h"
#include "nlist.h"

// TODO: negative indicies to index from the back of lists

/**
 * @brief Move each list element one index to the right, assumes the list has
 * allocated memory for one more element
 *
 * @param list list to right shift
 */
static void list_shift_right(const list_t *list) {
  if (list->cur_size >= list->max_size) {
    err_index_out_of_bounds(list->cur_size, list->max_size);
  }

  for (size_t i = list->cur_size; i > 0; i--) {
    list->entries[i] = list->entries[i - 1];
  }
}

/**
 * @brief Move each list element one index to the left, element at index 0 will
 * be overwritten
 *
 * @param list list to right shift
 */
static void list_shift_left(const list_t *list) {
  if (list->cur_size >= list->max_size) {
    err_index_out_of_bounds(list->cur_size, list->max_size);
  }

  for (size_t i = 1; i < list->cur_size; i++) {
    list->entries[i - 1] = list->entries[i];
  }
}

/**
 * @brief Expand max capacity of a list
 *
 * @param list list to expand
 */
static void list_expand(list_t *list) {
  size_t new_size = list->max_size * 2;
  list->entries = realloc(list->entries, new_size * sizeof(list->entries));
  if (list->entries == NULL) {
    free(list);
    err_malloc_fail();
  }

  list->max_size = new_size;
}

/**
 * @brief Checks if a value is present in a list.
 *
 * @param list list to check in
 * @param val value to check for
 * @return 1 if present 0 if not
 */
int list_contains(const list_t *list, void *val) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    if (list->entries[i] == val) {
      return 1;
    }
  }

  return 0;
}

/**
 * @brief Initialize a malloc'd list with malloc'd list->values
 *
 * @param init_size initial max size of list
 * @param type_size amount of bytes used for each element in the list
 * @return a malloc'd list that should to be freed using list_free()
 */
list_t *list_init(const size_t init_size) {
  list_t *list = malloc(sizeof(*list));
  if (list == NULL) {
    err_malloc_fail();
  }

  list->max_size = init_size;
  list->cur_size = 0;
  list->entries = malloc(init_size * sizeof(list->entries));
  if (list->entries == NULL) {
    free(list);
    err_malloc_fail();
  }

  return list;
}

/**
 * @brief Get a value in a list in O(1) time
 *
 * @param list list to index
 * @param index index into list
 */
void *list_get(const list_t *list, const size_t index) {
  if (index >= list->cur_size) {
    err_index_out_of_bounds(index, list->cur_size);
  }

  return list->entries[index];
}

/**
 * @brief Pops the last element of the list and return it
 *
 * @param list list to pop from
 * @return element at the end of the list
 */
void *list_pop_back(list_t *list) {
  if (list->cur_size == 0) {
    return NULL;
  }

  return list->entries[--list->cur_size];
}

/**
 * @brief Pops the first element of the list and return it
 *
 * @param list list to pop from
 * @return element at the end of the list
 */
void *list_pop_front(list_t *list) {
  if (list->cur_size == 0) {
    return NULL;
  }

  // Save retun value before it gets overwritten by list_left_shift
  void *popped = list->entries[0];
  list_shift_left(list);
  --list->cur_size;

  return popped;
}

/**
 * @brief Clear all values in list
 *
 * @param list list to clear
 */
void list_clear(list_t *list) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    list->entries[i] = NULL;
  }

  list->cur_size = 0;
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
void list_map(list_t *list, void(func)(void *)) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    func(list->entries[i]);
  }
}

/**
 * @brief Prints the bytes at each index in the list
 *
 * @param list list to print bytes of
 */
void list_print(list_t *list) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    printf("[%zu]: ", i);
    void *at_i = list_get(list, i);
    for (size_t j = 0; j < sizeof(void *); ++j) {
      printf("%02x ", *(char *)(at_i + j));
    }
    putchar('\n');
  }
}

/**
 * @brief Push a value to the end of a list by copying the bytes in val
 *
 * @param list list to push onto
 * @param val value to push onto the list
 */
void list_push_back(list_t *list, void *val) {
  // Resize if necessary
  if (list->cur_size == list->max_size) {
    list_expand(list);
  }

  list->entries[list->cur_size] = val;
  ++list->cur_size;
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
  if (list->cur_size == list->max_size) {
    list_expand(list);
  }

  if (list->cur_size > 0) {
    list_shift_right(list);
  }

  list->entries[0] = val;
  ++list->cur_size;
}

// TODO: implement
void list_reverse(list_t *list);
void list_remove(list_t *list, void *val);
