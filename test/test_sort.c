#include <assert.h>
#include <stdio.h>

#include "sort.h"

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
