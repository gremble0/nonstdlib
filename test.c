#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "hashtable.h"
#include "sort.h"
#include "array.h"

void test_hashtable(void) {
    printf("Testing hash table data structure...\n");

    ht_t *table = ht_init(5);
    ht_put(table, "asd", "YOYO");
    assert(table->n_entries == 1);
    ht_put(table, "asd", "YAYA");
    assert(table->n_entries == 1);
    ht_put(table, "qwerty", "123");
    assert(table->n_entries == 2);
    ht_put(table, "qwertz", "BABA");
    assert(table->n_entries == 3);
    ht_put(table, "qwertyb", "POPO");
    assert(table->n_entries == 4);

    assert(strcmp(ht_get(table, "asd"), "YAYA") == 0);
    assert(strcmp(ht_get(table, "qwerty"), "123") == 0);
    assert(strcmp(ht_get(table, "qwertz"), "BABA") == 0);
    assert(table->max_entries == 10);

    ht_put(table, "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfjlaksdjfkd\
ajsdklfaskldfkasjldhfkljashdfklahsdfklhasdkljfhasdkjlhfkjlashdfkljashdfkljhasdklfhkk\
ajsdhfkjlahsdkjflhaskldfhkljasdfkjasdfkashfklahsdkfljhaskljdhkajlshdfkjlahsdkljhakld\
sdhfkjlashdfkljhakjsldjashdfklalskdflkfhqwoliefhuqiowefiwlfiwelaufrawilerfilwhrfiklu\
hfruilwehrfiluaweriulhweuirlhweiurhuweuiruhiweuhruqwueirlweihfilweufqwelfhiuweihrqlw\
iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirluhqwuierhqwelrihqweirulhqwieurh", "POPO");
    assert(table->n_entries == 5);
    ht_put(table, "", "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfjlaksdjfkd\
ajsdklfaskldfkasjldhfkljashdfklahsdfklhasdkljfhasdkjlhfkjlashdfkljashdfkljhasdklfhkk\
ajsdhfkjlahsdkjflhaskldfhkljasdfkjasdfkashfklahsdkfljhaskljdhkajlshdfkjlahsdkljhakld\
sdhfkjlashdfkljhakjsldjashdfklalskdflkfhqwoliefhuqiowefiwlfiwelaufrawilerfilwhrfiklu\
hfruilwehrfiluaweriulhweuirlhweiurhuweuiruhiweuhruqwueirlweihfilweufqwelfhiuweihrqlw\
iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirluhqwuierhqwelrihqweirulhqwieurh");
    assert(table->n_entries == 6);
    assert(table->max_entries == 20);

    ht_free(table);

    printf("\033[0;32mAll hash table data structure tests passed\033[0;37m\n");
}

void test_stack(void) {
    printf("Testing stack data structure...\n");
    stack *s = stack_init();

    uint32_t *val1 = malloc(sizeof(uint32_t));
    uint32_t *val2 = malloc(sizeof(uint32_t));
    uint32_t *val3 = malloc(sizeof(uint32_t));
    *val1 = 1;
    *val2 = 2;
    *val3 = 3;
    stack_push(s, val1);
    stack_push(s, val2);
    stack_push(s, val3);

    assert(s->size == 3);
    assert(*(uint32_t *)stack_get(s, 0) == 3);
    assert(*(uint32_t *)stack_get(s, 1) == 2);
    assert(*(uint32_t *)stack_get(s, 2) == 1);

    uint32_t *popped1 = stack_pop(s);
    uint32_t *popped2 = stack_pop(s);
    uint32_t *popped3 = stack_pop(s);

    assert(s->size == 0);
    assert(*popped1 == 3);
    assert(*popped2 == 2);
    assert(*popped3 == 1);

    assert(popped3 == val1);
    assert(popped2 == val2);
    assert(popped1 == val3);
    assert(stack_pop(s) == NULL);

    free(val1);
    free(val2);
    free(val3);

    char *val4 = malloc(sizeof(char));
    uint64_t *val5 = malloc(sizeof(uint64_t));
    *val4 = 't';
    *val5 = 1000;
    stack_push(s, val4);
    stack_push(s, val5);
    
    assert(*(uint64_t *)stack_pop(s) == 1000);
    assert(*(char *)stack_pop(s) == 't');

    free(val4);
    free(val5);
    stack_free(s);

    printf("\033[0;32mAll stack data structure tests passed\033[0;37m\n");
}

void test_sort(sorting_algorithm sa) {
    int nums[] = { 5, 1, 4, 2, 8 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);
    int sorted[] = { 1, 2, 4, 5, 8 };

    int nums2[] = { 5555, 1, 22, 421, 0, 155, -14, -95 };
    const int nums2_size = sizeof(nums2)/sizeof(nums2[0]);
    int sorted2[] = { -95, -14, 0, 1, 22, 155, 421, 5555 };

    int nums3[] = { 1, -1, 1, 5, 2, 3, -1, 2, -1 };
    const int nums3_size = sizeof(nums3)/sizeof(nums3[0]);
    int sorted3[] = { -1, -1, -1, 1, 1, 2, 2, 3, 5 };

    sort(nums, nums_size, sa);
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == sorted[i]);
    }

    sort(nums2, nums2_size, sa);
    for (int i = 0; i < nums2_size; i++) {
        assert(nums2[i] == sorted2[i]);
    }

    sort(nums3, nums3_size, sa);
    for (int i = 0; i < nums3_size; i++) {
        assert(nums3[i] == sorted3[i]);
    }

    printf("\033[0;32mTest successful for sorting algorithm %d\033[0;37m\n", sa);
}

void test_all_sorts(void) {
    printf("Testing sorting algorithms...\n");
    int nums[] = { 7, 2, 1, 6, 8, 5, 3, 4 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);

    swap(nums, 0, 4);
    int swapped[] = { 8, 2, 1, 6, 7, 5, 3, 4 };
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == swapped[i]);
    }

    swap(nums, 0, nums_size - 1);
    int swapped2[] = { 4, 2, 1, 6, 7, 5, 3, 8 };
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == swapped2[i]);
    }

    for (int i = 0; i < NUM_SORT_ALGOS; ++i) {
        test_sort(i);
    }

    printf("\033[0;32mAll sorting algorithms tests passed\033[0;37m\n");
}

void test_arr(void) {
    printf("Testing array functions...\n");
    int nums[] = { 1, 2, 3, 4 };
    int present1 = 1;
    int present2 = 2;
    int present3 = 3;
    int present4 = 4;
    int absent1 = 0;
    int absent2 = 5;

    assert(arr_contains(nums, sizeof(nums)/sizeof(nums[0]), &present1, sizeof(int)));
    assert(arr_contains(nums, sizeof(nums)/sizeof(nums[0]), &present2, sizeof(int)));
    assert(arr_contains(nums, sizeof(nums)/sizeof(nums[0]), &present3, sizeof(int)));
    assert(arr_contains(nums, sizeof(nums)/sizeof(nums[0]), &present4, sizeof(int)));
    assert(!arr_contains(nums, sizeof(nums)/sizeof(nums[0]), &absent1, sizeof(int)));
    assert(!arr_contains(nums, sizeof(nums)/sizeof(nums[0]), &absent2, sizeof(int)));

    printf("\033[0;32mAll arr_contains tests passed\033[0;37m\n");

    printf("\033[0;32mAll array function tests passed\033[0;37m\n");
}

int main(void) {
    printf("------------------------------------------\n");
    test_hashtable();
    printf("------------------------------------------\n");
    test_stack();
    printf("------------------------------------------\n");
    test_all_sorts();
    printf("------------------------------------------\n");
    test_arr();
    printf("------------------------------------------\n");
}
