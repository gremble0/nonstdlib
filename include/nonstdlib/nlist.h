#pragma once

#include <stddef.h>

typedef struct {
  void **entries;  // List of all values
  size_t size;     // How many values are currently in the list
  size_t capacity; // The current maximum amount of elements (can be increased)
} list_t;

// Useful to cast functions that do not explicitly take a void * as a parameter.
// for example if you have a function `void do_something(char *) { ... }` and
// you have a list of `char *` you can cast it to a list_map_func in calls to
// list_map like: `list_map(list, (list_map_func)do_something)`
typedef void (*list_map_func)(void *);

int list_contains(const list_t *list, const void *val);
list_t *list_init(size_t init_size);
void *list_get(const list_t *list, size_t index);
void *list_pop_at(list_t *list, size_t index);
void *list_pop_back(list_t *list);
void *list_pop_front(list_t *list);
void *list_remove(list_t *list, void *val);
void list_clear(list_t *list);
void list_free(list_t *list);
void list_map(const list_t *list, list_map_func func);
void list_print(const list_t *list);
void list_push_back(list_t *list, void *val);
void list_push_front(list_t *list, void *val);
void list_reverse(list_t *list);
