#include "nerror.h"
#include "nsort.h"
#include "test.h"

static void test_sort(void (*sort_func)(int[], int)) {
  int nums[] = {5, 1, 4, 2, 8};
  const int nums_size = sizeof(nums) / sizeof(nums[0]);
  int sorted[] = {1, 2, 4, 5, 8};

  int nums2[] = {5555, 1, 22, 421, 0, 155, -14, -95};
  const int nums2_size = sizeof(nums2) / sizeof(nums2[0]);
  int sorted2[] = {-95, -14, 0, 1, 22, 155, 421, 5555};

  int nums3[] = {1, -1, 1, 5, 2, 3, -1, 2, -1};
  const int nums3_size = sizeof(nums3) / sizeof(nums3[0]);
  int sorted3[] = {-1, -1, -1, 1, 1, 2, 2, 3, 5};

  sort_func(nums, nums_size);
  for (int i = 0; i < nums_size; i++)
    DEBUG_ASSERT(nums[i] == sorted[i]);

  sort_func(nums2, nums2_size);
  for (int i = 0; i < nums2_size; i++)
    DEBUG_ASSERT(nums2[i] == sorted2[i]);

  sort_func(nums3, nums3_size);
  for (int i = 0; i < nums3_size; i++)
    DEBUG_ASSERT(nums3[i] == sorted3[i]);
}

void test_all_sorts() {
  TEST_MODULE_START("sort");

  test_sort(bubblesort);
  test_sort(insertionsort);
  test_sort(quicksort);
  test_sort(selectionsort);

  TEST_MODULE_END("sort");
}
