#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_init(const int init_size, const size_t type_size) {
    list_t *list = malloc(sizeof(list_t));
    list->max_size = init_size;
    list->cur_size = 0;
    list->type_size = type_size;
    list->values = malloc(init_size * type_size);

    return list;
}

void list_append(list_t *list, const void *val) {
    if (list->cur_size == list->max_size) {
        list->values = realloc(list, list->max_size * 2);
        list->max_size = list->max_size * 2;
    }

    memcpy(list->values + list->cur_size * list->type_size, val, list->type_size);
    ++list->cur_size;
}

void *list_get(list_t *list, const int index) {
    void *ret = malloc(sizeof(void*));
    memcpy(ret, list->values + index * list->type_size, list->type_size);
    return ret;
}
