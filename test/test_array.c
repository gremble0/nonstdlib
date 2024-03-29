#include <stdio.h>
#include <string.h>

#include "narray.h"
#include "test.h"

static int tests_passed = 0;
static int tests_ran = 0;

static void test_arr_clear(void) {
  int nums[] = {1, 2, 3, 4, 5, 6};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);

  char chars[] = {'a', 'b', 'c'};
  const size_t chars_size = sizeof(chars) / sizeof(chars[0]);

  char *strings[] = {"hello", "this", "is", "nonstdlib"};
  const int strings_size = sizeof(strings) / sizeof(strings[0]);

  arr_clear(nums, nums_size, sizeof(int));
  for (size_t i = 0; i < nums_size; ++i) {
    ASSERT_TRUE(nums[i] == 0);
  }

  arr_clear(chars, chars_size, sizeof(char));
  for (size_t i = 0; i < chars_size; ++i) {
    ASSERT_TRUE(chars[i] == 0);
  }

  arr_clear(strings, strings_size, sizeof(char *));
  for (size_t i = 0; i < strings_size; ++i) {
    ASSERT_TRUE(strings[i] == 0);
  }

defer:
  TEST_FUNCTION_SUCCESS();
}

static void test_arr_contains(void) {
  int nums[] = {1, 2, 3, 4};
  int present1 = 1;
  int present2 = 2;
  int present3 = 3;
  int present4 = 4;
  int absent1 = 0;
  int absent2 = 5;

  ASSERT_TRUE(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present1,
                           sizeof(int)));
  ASSERT_TRUE(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present2,
                           sizeof(int)));
  ASSERT_TRUE(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present3,
                           sizeof(int)));
  ASSERT_TRUE(arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &present4,
                           sizeof(int)));
  ASSERT_TRUE(!arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &absent1,
                            sizeof(int)));
  ASSERT_TRUE(!arr_contains(nums, sizeof(nums) / sizeof(nums[0]), &absent2,
                            sizeof(int)));

defer:
  TEST_FUNCTION_SUCCESS();
}

static void test_arr_equals(void) {
  int nums[] = {1, 2, 3, 4, 5, 6};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);

  int nums2[] = {1, 2, 3, 4, 5, 6};
  const int nums2_size = sizeof(nums2) / sizeof(nums2[0]);

  char chars[] = {'a', 'b', 'c'};
  const size_t chars_size = sizeof(chars) / sizeof(chars[0]);

  ASSERT_TRUE(arr_equals(nums, nums_size, nums2, nums2_size, sizeof(int)) == 1);
  ASSERT_TRUE(arr_equals(nums, nums_size, nums, nums_size, sizeof(int)) == 1);
  ASSERT_TRUE(arr_equals(nums, nums_size, chars, chars_size, sizeof(int)) == 0);

  int *nested[] = {nums, nums2};
  const size_t nested_size = sizeof(nested) / sizeof(nested[0]);

  int nested2[][7] = {{1, 2, 3, 4, 5, 6}, {1, 2, 3, 4, 5, 6}};
  const size_t nested2_size = sizeof(nested2) / sizeof(nested2[0]);

  int *nested3[] = {nums, nums2};
  const size_t nested3_size = sizeof(nested3) / sizeof(nested3[0]);

  ASSERT_TRUE(
      arr_equals(nested, nested_size, nested2, nested2_size, sizeof(int)) == 0);
  ASSERT_TRUE(
      arr_equals(nested, nested_size, nested3, nested3_size, sizeof(int)) == 1);

defer:
  TEST_FUNCTION_SUCCESS();
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
  for (size_t i = 0; i < nums_size; ++i) {
    ASSERT_TRUE(nums[i] == nums_reversed[i]);
  }

  arr_reverse(chars, chars_size, sizeof(char));
  for (size_t i = 0; i < chars_size; ++i) {
    ASSERT_TRUE(chars[i] == chars_reversed[i]);
  }

  arr_reverse(strings, strings_size, sizeof(char *));
  for (size_t i = 0; i < strings_size; ++i) {
    ASSERT_TRUE(strcmp(strings[i], strings_reversed[i]) == 0);
  }

defer:
  TEST_FUNCTION_SUCCESS();
}

static void test_arr_swap(void) {
  int nums[] = {1, 2, 3};
  arr_swap(nums, 0, 1, sizeof(int));
  ASSERT_TRUE(nums[0] == 2);
  ASSERT_TRUE(nums[1] == 1);
  ASSERT_TRUE(nums[2] == 3);
  arr_swap(nums, 1, 0, sizeof(int));
  ASSERT_TRUE(nums[0] == 1);
  ASSERT_TRUE(nums[1] == 2);
  ASSERT_TRUE(nums[2] == 3);

  char chars[] = {'a', 'b', 'c', 'd'};
  arr_swap(chars, 1, 3, sizeof(char));
  ASSERT_TRUE(chars[0] == 'a');
  ASSERT_TRUE(chars[1] == 'd');
  ASSERT_TRUE(chars[2] == 'c');
  ASSERT_TRUE(chars[3] == 'b');

  char *strings[] = {"hello", "this", "is", "nonstdlib"};
  arr_swap(strings, 0, 1, sizeof(char *));
  ASSERT_TRUE(strcmp(strings[0], "this") == 0);
  ASSERT_TRUE(strcmp(strings[1], "hello") == 0);
  ASSERT_TRUE(strcmp(strings[2], "is") == 0);
  ASSERT_TRUE(strcmp(strings[3], "nonstdlib") == 0);

defer:
  TEST_FUNCTION_SUCCESS();
}

void test_arr(int *total_tests_ran, int *total_tests_passed) {
  TEST_MODULE_START();

  test_arr_clear();
  test_arr_contains();
  test_arr_equals();
  test_arr_swap();
  test_arr_reverse();

  TEST_MODULE_END();

  *total_tests_passed += tests_passed;
  *total_tests_ran += tests_ran;
}
