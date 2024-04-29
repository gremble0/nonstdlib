#include "nonstdlib/nsort.h"
#include "nonstdlib/narray.h"

/**
 * @brief Sort an array using some sorting algorithm
 *
 * @param arr  array to sort
 * @param size size of array to sort
 * @param sa   what sorting algorithm to use for sorting
 */
void sort(int *arr, int size, sorting_algorithm sa) {
  switch (sa) {
  case BUBBLESORT:
    bubblesort(arr, size);
    break;
  case QUICKSORT:
    quicksort(arr, size);
    break;
  case INSERTIONSORT:
    insertionsort(arr, size);
    break;
  case SELECTIONSORT:
    selectionsort(arr, size);
    break;
  }
}

/**
 * @brief Semi recursive implementation of bubblesort
 *
 * @param arr  array to be sorted
 * @param size size of the array to sort
 */
void bubblesort(int *arr, int size) {
  char swapped = 0;
  // Loop through each number
  for (int i = 0; i < size - 1; ++i) {
    // Propogate as far down the array as we can one index at a time
    // (We could also use an if test to only swap once, but then we would
    // just have to do more recursive calls instead)
    for (int j = i; arr[j] > arr[j + 1] && j < size - 1; ++j) {
      arr_swap(arr, j, j + 1, sizeof(int));
      swapped = 1;
    }
  }

  if (swapped)
    // After one full iteration of the array, we know we have moved at least one
    // element to the end of the array, so we can decrement the size for the
    // next recursive call
    bubblesort(arr, size - 1);
}

/**
 * @brief Iterative implementation of insertionsort
 *
 * @param arr  array to be sorted
 * @param size size of the array to sort
 */
void insertionsort(int *arr, int size) {
  for (int i = 1; i < size; ++i)
    for (int j = i; arr[j - 1] > arr[j] && j > 0; --j)
      arr_swap(arr, j - 1, j, sizeof(int));
}

/**
 * @brief Recursive implementation of the quicksort algorithm
 *
 * @param arr   array to sort
 * @param start the start index in the array for this iteration of recursion
 * @param end   the end index in the array for this iteration of recursion
 */
void quicksort_impl(int *arr, int start, int end) {
  // basecase
  if (start >= end)
    return;

  // Choose pivot element (here just use the last element in the array)
  int pivot = arr[end - 1];

  int left_i = start;
  int right_i = end - 2;
  // Increment left_i until arr[left_i] is greater than pivot
  while (arr[left_i] < pivot && ++left_i)
    ;
  // Decrement right_i until arr[right_i] is less than pivot
  while (arr[right_i] >= pivot && --right_i)
    ;

  if (left_i < right_i) {
    // If left_i < right_i there are still more elements smaller than the pivot
    // that need to be moved to the front of the array
    arr_swap(arr, left_i, right_i, sizeof(int));
    quicksort_impl(arr, start, end);
  } else {
    // Otherwise we are done with this partition and we continue splitting
    // the array into 2 new partitions and sort them
    arr_swap(arr, left_i, end - 1, sizeof(int)); // swap left with pivot
    quicksort_impl(arr, start, left_i);
    quicksort_impl(arr, left_i + 1, end);
  }
}

/**
 * @brief Wrapper function around the actual implementation of the quicksort
 *        algorithm so that consumers don't need to specify the initial start
 *        value which is always zero
 *
 * @param arr  array to be sorted
 * @param size size of the array to sort
 */
void quicksort(int *arr, int size) { quicksort_impl(arr, 0, size); }

/**
 * @brief Iterative implementation of selection sort
 *
 * @param arr  array to be sorted
 * @param size size of the array to sort
 */
void selectionsort(int *arr, int size) {
  // Index of smallest number seen in current iteration
  int min_i = 0;
  for (int i = 0; i < size;) {
    for (int j = i; j < size; ++j)
      if (arr[j] < arr[min_i])
        min_i = j;

    arr_swap(arr, min_i, i, sizeof(int));
    min_i = ++i;
  }
}
