#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

void test_list(void) {
    printf("Testing list data structure...\n");

    list_t *list = list_init(5, sizeof(int));

    list_append(list, "a");
    list_append(list, "asd");
    assert(strcmp("a", list_get(list, 0)) == 0);
    assert(strcmp("asd", list_get(list, 1)) == 0);
    assert(list->cur_size == 2);

    list_clear(list);
    list_append(list, "b");
    assert(strcmp("b", list_get(list, 0)) == 0);
    assert(list->cur_size == 1);

    list_free(list);

    printf("\033[0;32mAll list tests passed\033[0;37m\n");
}
