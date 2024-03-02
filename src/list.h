#pragma once

#include <stddef.h>

// TODO: make error.h
// TODO: goto catch??
// Some kind of inheritance for error handling
#define ERROR(type, errstr, ...)                                               \
  fprintf(stderr, type ": " errstr "\nIn call to function: '%s'\n",            \
          __VA_ARGS__, __func__);                                              \
  exit(1)

#define ERROR_MALLOC_FAIL()                                                    \
  ERROR("MALLOC_FAIL", "Memory allocation returned (nil)")

#define ERROR_INDEX_OUT_OF_BOUNDS(index, max_index)                            \
  ERROR("INDEX_OUT_OF_BOUNDS",                                                 \
        "index %zu out of bounds where max_index is %zu", index, max_index);

typedef struct list_t {
  void **values;    // List of all values
  size_t type_size; // Size of one value in the list
  size_t cur_size;  // How many values are currently in the list
  size_t max_size;  // What is the current maximum amount of elements (can be
                    // increased)
} list_t;

int list_contains(list_t *list, const void *val);
list_t *list_init(const size_t init_size, const size_t type_size);
void *list_get(list_t *list, const size_t index);
void *list_pop_back(list_t *list);
void *list_pop_front(list_t *list);
void list_clear(list_t *list);
void list_free(list_t *list);
void list_print(list_t *list);
void list_push_back(list_t *list, const void *val);
void list_push_front(list_t *list, const void *val);
void list_remove(list_t *list, const void *val);
void list_reverse(list_t *list);
