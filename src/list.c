#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_init(const int init_size, const int type_size) {
    list_t *list = malloc(sizeof(list_t));
    list->max_size = init_size;
    list->cur_size = 0;
    list->type_size = type_size;
    list->values = malloc(init_size * type_size);

    return list;
}

void list_append(list_t *list, const void *val) {
    if (list->cur_size == list->max_size) {
        list = realloc(list, list->max_size * 2);
    }

    memcpy(list->values + list->cur_size * list->type_size, val, list->type_size);
}
