#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "list.h"

void test_list(void) {
    printf("Testing list data structure...\n");

    list_t *list = list_init(5, sizeof(char*));

    list_append(list, "a");
    list_append(list, "asd");
    assert(strcmp("a", list_get(list, 0)) == 0);
    assert(strcmp("asd", list_get(list, 1)) == 0);
    assert(list->cur_size == 2);

    list_clear(list);
    list_append(list, "b");
    assert(strcmp("b", list_get(list, 0)) == 0);
    assert(list->cur_size == 1);

    const int a = 2;
    const long long b = 44;
    assert(list_contains(list, "a") == 0);
    assert(list_contains(list, "b") == 1);
    assert(list_contains(list, &a) == 0);
    assert(list_contains(list, &b) == 0);

    list_free(list);

    printf("\033[0;32mAll list tests passed\033[0;37m\n");
}
