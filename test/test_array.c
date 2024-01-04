#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "array.h"

void test_arr_contains(void) {
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
}

void test_arr_reverse(void) {
    int nums[] = { 1, 2, 3, 4, 5, 6 };
    const int nums_size = sizeof(nums)/sizeof(nums[0]);
    int nums_reversed[] = { 6, 5, 4, 3, 2, 1 };

    char chars[] = { 'a', 'b', 'c' };
    const size_t chars_size = sizeof(chars)/sizeof(chars[0]);
    char chars_reversed[] = { 'c', 'b', 'a' };

    char *strings[] = { "hello", "this", "is", "nonstdlib" };
    const int strings_size = sizeof(strings)/sizeof(strings[0]);
    char *strings_reversed[] = { "nonstdlib", "is", "this", "hello" };

    arr_reverse(nums, nums_size, sizeof(int));
    for (size_t i = 0; i < nums_size; ++i) {
        assert(nums[i] == nums_reversed[i]);
    }

    arr_reverse(chars, chars_size, sizeof(char));
    for (size_t i = 0; i < chars_size; ++i) {
        assert(chars[i] == chars_reversed[i]);
    }

    arr_reverse(strings, strings_size, sizeof(char*));
    for (size_t i = 0; i < strings_size; ++i) {
        assert(strcmp(strings[i], strings_reversed[i]) == 0);
    }

    printf("\033[0;32mAll arr_reversed tests passed\033[0;37m\n");
}

void test_arr_swap(void) {
    int nums[] = { 1, 2, 3 };
    arr_swap(nums, 0, 1, sizeof(int));
    assert(nums[0] == 2);
    assert(nums[1] == 1);
    assert(nums[2] == 3);
    arr_swap(nums, 1, 0, sizeof(int));
    assert(nums[0] == 1);
    assert(nums[1] == 2);
    assert(nums[2] == 3);

    char chars[] = { 'a', 'b', 'c', 'd' };
    arr_swap(chars, 1, 3, sizeof(char));
    assert(chars[0] == 'a');
    assert(chars[1] == 'd');
    assert(chars[2] == 'c');
    assert(chars[3] == 'b');

    char *strings[] = { "hello", "this", "is", "nonstdlib" };
    arr_swap(strings, 0, 1, sizeof(char*));
    assert(strcmp(strings[0], "this") == 0);
    assert(strcmp(strings[1], "hello") == 0);
    assert(strcmp(strings[2], "is") == 0);
    assert(strcmp(strings[3], "nonstdlib") == 0);
}

void test_arr(void) {
    printf("Testing array functions...\n");
    test_arr_contains();
    test_arr_swap();
    test_arr_reverse();
    printf("\033[0;32mAll array function tests passed\033[0;37m\n");
}

