#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// TODO: negative indicies to index from the back of lists

/**
 * @brief Checks if a value is present in a list
 *
 * @param list list to check in
 * @param val value to check for
 * @return 1 if present 0 if not
 */
int list_contains(list_t *list, const void *val) {
  for (size_t i = 0; i < list->cur_size; ++i) {
    if (memcmp(list->values + i * list->type_size, val, list->type_size) == 0) {
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
list_t *list_init(const int init_size, const size_t type_size) {
  list_t *list = malloc(sizeof(list_t));
  if (list == NULL) {
    return NULL;
  }

  list->max_size = init_size;
  list->cur_size = 0;
  list->type_size = type_size;
  list->values = malloc(init_size * type_size);
  if (list->values == NULL) {
    free(list);
    return NULL;
  }

  return list;
}

/**
 * @brief Pops the last element appended to the list
 *
 * @param list list to pop from
 * @return whatever is present at the end of the list
 */
void *list_pop(list_t *list) {
  if (list->cur_size == 0) {
    return NULL;
  }

  return list->values[list->cur_size--];
}

/**
 * @brief Get a value in a list in O(1) time complexity
 *
 * @param list list to index
 * @param index index into list
 */
void *list_get(list_t *list, const int index) {
  return list->values + index * list->type_size;
}

/**
 * @brief Append a value to the end of a list by copying the bytes in val
 *
 * @param list list to append onto
 * @param val value to append onto the list
 */
void list_append(list_t *list, const void *val) {
  if (list->cur_size == list->max_size) {
    list->max_size *= 2;
    list->values = realloc(list->values, list->max_size);
  }

  memcpy(list->values + list->cur_size * list->type_size, val, list->type_size);
  ++list->cur_size;
}

/**
 * @brief Clear all values in list
 *
 * @param list list to clear
 */
void list_clear(list_t *list) {
  memset(list->values, 0, list->cur_size * list->type_size);
  list->cur_size = 0;
}

/**
 * @brief Free all variables bound to a list
 *
 * @param list list to free
 */
void list_free(list_t *list) {
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
