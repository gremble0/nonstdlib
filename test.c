#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "hashtable.h"
#include "sort.h"

void test_hashtable(void) {
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
}

void test_stack(void) {
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
}

// TODO generic sorting test function
void test_quicksort(void) {
    int nums[] = { 7, 2, 1, 6, 8, 5, 3, 4 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);
    int sorted[] = { 1, 2, 3, 4, 5, 6, 7, 8 };

    int nums2[] = { 5555, 1, 22, 421, 0, 155, -14, -95 };
    const int nums2_size = sizeof(nums2)/sizeof(nums2[0]);
    int sorted2[] = { -95, -14, 0, 1, 22, 155, 421, 5555 };

    sort(nums, nums_size, QUICKSORT);
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == sorted[i]);
    }

    sort(nums2, nums2_size, QUICKSORT);
    for (int i = 0; i < nums2_size; i++) {
        assert(nums2[i] == sorted2[i]);
    }
}

void test_bubblesort(void) {
    int nums[] = { 5, 1, 4, 2, 8 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);
    int sorted[] = { 1, 2, 4, 5, 8 };

    int nums2[] = { 5555, 1, 22, 421, 0, 155, -14, -95 };
    const int nums2_size = sizeof(nums2)/sizeof(nums2[0]);
    int sorted2[] = { -95, -14, 0, 1, 22, 155, 421, 5555 };

    sort(nums, nums_size, BUBBLESORT);
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == sorted[i]);
    }

    sort(nums2, nums2_size, BUBBLESORT);
    for (int i = 0; i < nums2_size; i++) {
        assert(nums2[i] == sorted2[i]);
    }
}

void test_insertionsort(void) {
    int nums[] = { 5, 1, 4, 2, 8 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);
    int sorted[] = { 1, 2, 4, 5, 8 };

    int nums2[] = { 5555, 1, 22, 421, 0, 155, -14, -95 };
    const int nums2_size = sizeof(nums2)/sizeof(nums2[0]);
    int sorted2[] = { -95, -14, 0, 1, 22, 155, 421, 5555 };

    sort(nums, nums_size, INSERTIONSORT);
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == sorted[i]);
    }

    sort(nums2, nums2_size, INSERTIONSORT);
    for (int i = 0; i < nums2_size; i++) {
        assert(nums2[i] == sorted2[i]);
    }
}

void test_selectionsort(void) {
    int nums[] = { 5, 1, 4, 2, 8 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);
    int sorted[] = { 1, 2, 4, 5, 8 };

    int nums2[] = { 5555, 1, 22, 421, 0, 155, -14, -95 };
    const int nums2_size = sizeof(nums2)/sizeof(nums2[0]);
    int sorted2[] = { -95, -14, 0, 1, 22, 155, 421, 5555 };

    sort(nums, nums_size, SELECTIONSORT);
    for (int i = 0; i < nums_size; i++) {
        assert(nums[i] == sorted[i]);
    }

    sort(nums2, nums2_size, SELECTIONSORT);
    for (int i = 0; i < nums2_size; i++) {
        assert(nums2[i] == sorted2[i]);
    }
}

void test_sort(void) {
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

    test_quicksort();
    test_bubblesort();
    test_insertionsort();
    test_selectionsort();
}

int main(void) {
    test_hashtable();
    test_stack();
    test_sort();
}
