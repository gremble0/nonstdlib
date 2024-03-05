#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "list.h"

// TODO: negative indicies to index from the back of lists
// TODO: list_of function

/**
 * @brief Move each list element one index to the right, assumes the list has
 * allocated memory for one more element
 *
 * @param list list to right shift
 */
static void list_shift_right(list_t *list) {
  if (list->cur_size >= list->max_size) {
    err_index_out_of_bounds(list->cur_size, list->max_size);
  }

  for (size_t i = list->cur_size; i > 0; i--) {
    memcpy(list->values[i], list->values[i - 1], list->type_size);
  }
}

/**
 * @brief Move each list element one index to the left, element at index 0 will
 * be overwritten
 *
 * @param list list to right shift
 */
static void list_shift_left(list_t *list) {
  if (list->cur_size >= list->max_size) {
    err_index_out_of_bounds(list->cur_size, list->max_size);
  }

  for (size_t i = 1; i < list->cur_size; i++) {
    memcpy(list->values[i - 1], list->values[i], list->type_size);
  }
}

static void list_expand(list_t *list) {
  list->max_size *= 2;
  list->values = realloc(list->values, list->max_size);
  if (list->values == NULL) {
    err_malloc_fail();
  }
}

/**
 * @brief Checks if a value is present in a list.
 *
 * @param list list to check in
 * @param val value to check for
 * @return 1 if present 0 if not
 */
int list_contains(list_t *list, const void *val) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    if (memcmp(list->values[i], val, list->type_size) == 0) {
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
list_t *list_init(const size_t init_size, const size_t type_size) {
  list_t *list = malloc(sizeof(list_t));
  if (list == NULL) {
    err_malloc_fail();
  }

  list->max_size = init_size;
  list->cur_size = 0;
  list->type_size = type_size;
  list->values = malloc(init_size * sizeof(void *));
  if (list->values == NULL) {
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
void *list_get(list_t *list, const size_t index) {
  if (index >= list->cur_size) {
    err_index_out_of_bounds(list->cur_size, list->max_size);
  }

  return list->values[index];
}

/**
 * @brief Pops the last element of the list and return it. Needs to be freed
 *
 * @param list list to pop from
 * @return element at the end of the list
 */
void *list_pop_back(list_t *list) {
  if (list->cur_size == 0) {
    return NULL;
  }

  // Save return value to new memory locatin independent of the list it was
  // popped from
  void *ret = malloc(list->type_size);
  if (ret == NULL) {
    err_malloc_fail();
  }

  --list->cur_size;
  memcpy(ret, list->values[list->cur_size], list->type_size);
  free(list->values[list->cur_size]);

  return ret;
}

/**
 * @brief Pops the first element of the list and return it. Needs to be freed
 *
 * @param list list to pop from
 * @return element at the end of the list
 */
void *list_pop_front(list_t *list) {
  if (list->cur_size == 0) {
    return NULL;
  }

  // Save retun value before it gets overwritten by list_left_shift
  void *ret = malloc(list->type_size);
  if (ret == NULL) {
    err_malloc_fail();
  }

  memcpy(ret, list->values[0], list->type_size);

  // Update list
  list_shift_left(list);

  --list->cur_size;
  // Memory has been moved around so freeing list->values[0] would free in use
  // memory. We need to free the value at the end previous instead
  free(list->values[list->cur_size]);

  return ret;
}

/**
 * @brief Clear all values in list
 *
 * @param list list to clear
 */
void list_clear(list_t *list) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    free(list->values[i]);
  }

  list->cur_size = 0;
}

/**
 * @brief Free all variables bound to a list
 *
 * @param list list to free
 */
void list_free(list_t *list) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    free(list->values[i]);
  }
  free(list->values);
  free(list);
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
    for (size_t j = 0; j < list->type_size; ++j) {
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
void list_push_back(list_t *list, const void *val) {
  // Resize if necessary
  if (list->cur_size == list->max_size) {
    list_expand(list);
  }

  // TODO: own function for this
  list->values[list->cur_size] = malloc(list->type_size);
  if (list->values[list->cur_size] == NULL) {
    list_free(list);
    err_malloc_fail();
  }

  memcpy(list->values[list->cur_size], val, list->type_size);
  ++list->cur_size;
}

/**
 * @brief Push a value to the start of a list by shifting the rest of the list
 * to the right and copying the bytes in val to the front
 *
 * @param list list to push onto
 * @param val value to push onto the list
 */
void list_push_front(list_t *list, const void *val) {
  // Resize if necessary
  if (list->cur_size == list->max_size) {
    list_expand(list);
  }

  list->values[list->cur_size] = malloc(list->type_size);
  if (list->values[list->cur_size] == NULL) {
    // TODO: freeing when malloc other places
    list_free(list);
    err_malloc_fail();
  }

  if (list->cur_size > 0) {
    list_shift_right(list);
  }

  memcpy(list->values[0], val, list->type_size);
  ++list->cur_size;
}

// TODO: implement
void list_reverse(list_t *list);
void list_remove(list_t *list, const void *val);
