#pragma once

#include <stddef.h>

typedef struct list_t {
    void *values;           // List of all values
    size_t type_size; // Size of one value in the list
    size_t cur_size;        // How many values are currently in the list
    size_t max_size;        // What is the current maximum amount of elements (can be increased)
} list_t;

void list_append(list_t *list, const void *val);
void list_clear(list_t *list);
int list_contains(list_t *list, const void *val);
void *list_get(list_t *list, const int index);
list_t *list_init(const int init_size, const size_t type_size);
void list_remove(list_t *list, const void *val);
void list_reverse(list_t *list);
void *list_pop(list_t *list);
void list_swap(list_t *list, int i, int j);
