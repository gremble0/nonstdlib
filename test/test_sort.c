#include <stdio.h>

#include "sort.h"
#include "test.h"

static int tests_passed = 0;
static int tests_ran = 0;

static void test_sort(sorting_algorithm sa) {
  int nums[] = {5, 1, 4, 2, 8};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);
  int sorted[] = {1, 2, 4, 5, 8};

  int nums2[] = {5555, 1, 22, 421, 0, 155, -14, -95};
  const int nums2_size = sizeof(nums2) / sizeof(nums2[0]);
  int sorted2[] = {-95, -14, 0, 1, 22, 155, 421, 5555};

  int nums3[] = {1, -1, 1, 5, 2, 3, -1, 2, -1};
  const int nums3_size = sizeof(nums3) / sizeof(nums3[0]);
  int sorted3[] = {-1, -1, -1, 1, 1, 2, 2, 3, 5};

  sort(nums, nums_size, sa);
  for (int i = 0; i < nums_size; i++) {
    ASSERT_TRUE(nums[i] == sorted[i]);
  }

  sort(nums2, nums2_size, sa);
  for (int i = 0; i < nums2_size; i++) {
    ASSERT_TRUE(nums2[i] == sorted2[i]);
  }

  sort(nums3, nums3_size, sa);
  for (int i = 0; i < nums3_size; i++) {
    ASSERT_TRUE(nums3[i] == sorted3[i]);
  }

defer:
  TEST_FUNCTION_SUCCESS();
}

void test_all_sorts(int *total_tests_ran, int *total_tests_passed) {
  TEST_MODULE_START();

  for (int i = 0; i < NUM_SORT_ALGOS; ++i) {
    test_sort(i);
  }

  TEST_MODULE_END();

  *total_tests_passed += tests_passed;
  *total_tests_ran += tests_ran;
}
