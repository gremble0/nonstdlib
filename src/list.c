#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * @brief Initialize a malloc'd list with malloc'd list->values
 *
 * @param init_size initial max size of list
 * @param type_size amount of bytes used for each element in the list
 * @return a malloc'd list that should to be freed using list_free()
 */
list_t *list_init(const int init_size, const size_t type_size) {
    list_t *list = malloc(sizeof(list_t));
    list->max_size = init_size;
    list->cur_size = 0;
    list->type_size = type_size;
    list->values = malloc(init_size * type_size);

    return list;
}

/**
 * @brief Append a value to the end of a list
 *
 * @param list list to append onto
 * @param val value to append onto the list
 */
void list_append(list_t *list, const void *val) {
    if (list->cur_size == list->max_size) {
        list->values = realloc(list, list->max_size * 2);
        list->max_size = list->max_size * 2;
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
 * @brief Free all variables bound to a list
 *
 * @param list list to free
 */
void list_free(list_t *list) {
    free(list->values);
    free(list);
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
