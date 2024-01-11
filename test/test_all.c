#include <stdio.h>

#include "test_array.c"
#include "test_hashtable.c"
#include "test_hashtable_generic.c"
#include "test_sort.c"
#include "test_stack.c"

int main(void) {
    printf("------------------------------------------\n");
    test_arr();
    printf("------------------------------------------\n");
    test_hashtable();
    printf("------------------------------------------\n");
    test_hashtable_generic();
    printf("------------------------------------------\n");
    test_all_sorts();
    printf("------------------------------------------\n");
    test_stack();
    printf("------------------------------------------\n");
}
