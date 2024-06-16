#include <stdio.h>
#include <string.h>

#include "nonstdlib/narray.h"
#include "nonstdlib/nerror.h"
#include "test.h"

static void test_arr_clear(void) {
  int nums[] = {1, 2, 3, 4, 5, 6};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);

  char chars[] = {'a', 'b', 'c'};
  const size_t chars_size = sizeof(chars) / sizeof(chars[0]);

  char *strings[] = {"hello", "this", "is", "nonstdlib"};
  const int strings_size = sizeof(strings) / sizeof(strings[0]);

  arr_clear(nums, nums_size, sizeof(int));
  for (size_t i = 0; i < nums_size; ++i)
    DEBUG_ASSERT(nums[i] == 0);

  arr_clear(chars, chars_size, sizeof(char));
  for (size_t i = 0; i < chars_size; ++i)
    DEBUG_ASSERT(chars[i] == 0);

  arr_clear(strings, strings_size, sizeof(char *));
  for (size_t i = 0; i < strings_size; ++i)
    DEBUG_ASSERT(strings[i] == 0);
}

static void test_arr_contains(void) {
  int nums[] = {1, 2, 3, 4};
  int present1 = 1;
  int present2 = 2;
  int present3 = 3;
  int present4 = 4;
  int absent1 = 0;
  int absent2 = 5;

  DEBUG_ASSERT(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present1, sizeof(int)));
  DEBUG_ASSERT(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present2, sizeof(int)));
  DEBUG_ASSERT(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present3, sizeof(int)));
  DEBUG_ASSERT(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present4, sizeof(int)));
  DEBUG_ASSERT(!arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &absent1, sizeof(int)));
  DEBUG_ASSERT(!arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &absent2, sizeof(int)));
}

static void test_arr_equals(void) {
  int nums[] = {1, 2, 3, 4, 5, 6};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);

  int nums2[] = {1, 2, 3, 4, 5, 6};
  const int nums2_size = sizeof(nums2) / sizeof(nums2[0]);

  char chars[] = {'a', 'b', 'c'};
  const size_t chars_size = sizeof(chars) / sizeof(chars[0]);

  DEBUG_ASSERT(arr_equals(nums, nums_size, nums2, nums2_size, sizeof(int)) == 1);
  DEBUG_ASSERT(arr_equals(nums, nums_size, nums, nums_size, sizeof(int)) == 1);
  DEBUG_ASSERT(arr_equals(nums, nums_size, chars, chars_size, sizeof(int)) == 0);

  int *nested[] = {nums, nums2};
  const size_t nested_size = sizeof(nested) / sizeof(nested[0]);

  int nested2[][7] = {{1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}};
  const size_t nested2_size = sizeof(nested2) / sizeof(nested2[0]);

  int *nested3[] = {nums, nums2};
  const size_t nested3_size = sizeof(nested3) / sizeof(nested3[0]);

  DEBUG_ASSERT(arr_equals(nested, nested_size, nested2, nested2_size, sizeof(int)) == 0);
  DEBUG_ASSERT(arr_equals(nested, nested_size, nested3, nested3_size, sizeof(int)) == 1);
}

static void test_arr_reverse(void) {
  int nums[] = {1, 2, 3, 4, 5, 6};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);
  int nums_reversed[] = {6, 5, 4, 3, 2, 1};

  char chars[] = {'a', 'b', 'c'};
  const size_t chars_size = sizeof(chars) / sizeof(chars[0]);
  char chars_reversed[] = {'c', 'b', 'a'};

  char *strings[] = {"hello", "this", "is", "nonstdlib"};
  const int strings_size = sizeof(strings) / sizeof(strings[0]);
  char *strings_reversed[] = {"nonstdlib", "is", "this", "hello"};

  arr_reverse(nums, nums_size, sizeof(int));
  for (size_t i = 0; i < nums_size; ++i)
    DEBUG_ASSERT(nums[i] == nums_reversed[i]);

  arr_reverse(chars, chars_size, sizeof(char));
  for (size_t i = 0; i < chars_size; ++i)
    DEBUG_ASSERT(chars[i] == chars_reversed[i]);

  arr_reverse(strings, strings_size, sizeof(char *));
  for (size_t i = 0; i < strings_size; ++i)
    DEBUG_ASSERT(strcmp(strings[i], strings_reversed[i]) == 0);
}

static void test_arr_swap(void) {
  int nums[] = {1, 2, 3};
  arr_swap(nums, 0, 1, sizeof(int));
  DEBUG_ASSERT(nums[0] == 2);
  DEBUG_ASSERT(nums[1] == 1);
  DEBUG_ASSERT(nums[2] == 3);
  arr_swap(nums, 1, 0, sizeof(int));
  DEBUG_ASSERT(nums[0] == 1);
  DEBUG_ASSERT(nums[1] == 2);
  DEBUG_ASSERT(nums[2] == 3);

  char chars[] = {'a', 'b', 'c', 'd'};
  arr_swap(chars, 1, 3, sizeof(char));
  DEBUG_ASSERT(chars[0] == 'a');
  DEBUG_ASSERT(chars[1] == 'd');
  DEBUG_ASSERT(chars[2] == 'c');
  DEBUG_ASSERT(chars[3] == 'b');

  char *strings[] = {"hello", "this", "is", "nonstdlib"};
  arr_swap(strings, 0, 1, sizeof(char *));
  DEBUG_ASSERT(strcmp(strings[0], "this") == 0);
  DEBUG_ASSERT(strcmp(strings[1], "hello") == 0);
  DEBUG_ASSERT(strcmp(strings[2], "is") == 0);
  DEBUG_ASSERT(strcmp(strings[3], "nonstdlib") == 0);
}

void test_arr() {
  TEST_MODULE_START("array");

  test_arr_clear();
  test_arr_contains();
  test_arr_equals();
  test_arr_swap();
  test_arr_reverse();

  TEST_MODULE_END("array");
}
