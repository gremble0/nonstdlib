#include "sort.h"
#include "array.h"

/**
 * @brief Sort an array using some sorting algorithm
 *
 * @param buf     array to sort
 * @param bufsize size of array to sort
 * @param sa      what sorting algorithm to use for sorting
 */
void sort(int buf[], int bufsize, sorting_algorithm sa) {
  switch (sa) {
  case BUBBLESORT:
    bubblesort(buf, bufsize);
    break;
  case QUICKSORT:
    quicksort(buf, bufsize);
    break;
  case INSERTIONSORT:
    insertionsort(buf, bufsize);
    break;
  case SELECTIONSORT:
    selectionsort(buf, bufsize);
    break;
  }
}

/**
 * @brief Semi recursive implementation of bubblesort
 *
 * @param buf     array to be sorted
 * @param bufsize size of the array to sort
 */
void bubblesort(int buf[], int bufsize) {
  char swapped = 0;
  // Loop through each number
  for (int i = 0; i < bufsize - 1; ++i) {
    // Propogate as far down the array as we can one index at a time
    // (We could also use an if test to only swap once, but then we would
    // just have to do more recursive calls instead)
    for (int j = i; buf[j] > buf[j + 1] && j < bufsize - 1; ++j) {
      arr_swap(buf, j, j + 1, sizeof(int));
      swapped = 1;
    }
  }

  if (swapped) {
    // After one full iteration of the array, we know we have moved at least one
    // element to the end of the array, so we can decrement the bufsize for the
    // next recursive call
    bubblesort(buf, bufsize - 1);
  }
}

/**
 * @brief Iterative implementation of insertionsort
 *
 * @param buf     array to be sorted
 * @param bufsize size of the array to sort
 */
void insertionsort(int buf[], int bufsize) {
  for (int i = 1; i < bufsize; ++i) {
    for (int j = i; buf[j - 1] > buf[j] && j > 0; --j) {
      arr_swap(buf, j - 1, j, sizeof(int));
    }
  }
}

/**
 * @brief Recursive implementation of the quicksort algorithm
 *
 * @param buf   array to sort
 * @param start the start index in the array for this iteration of recursion
 * @param end   the end index in the array for this iteration of recursion
 */
void quicksort_impl(int buf[], int start, int end) {
  // basecase
  if (start >= end) {
    return;
  }

  // Choose pivot element (here just use the last element in the array)
  int pivot = buf[end - 1];

  int left_i = start, right_i = end - 2;
  // Increment left_i until buf[left_i] is greater than pivot
  while (buf[left_i] < pivot && ++left_i)
    ;
  // Decrement right_i until buf[right_i] is less than pivot
  while (buf[right_i] >= pivot && --right_i)
    ;

  if (left_i < right_i) {
    // If left_i < right_i there are still more elements smaller than the pivot
    // that need to be moved to the front of the array
    arr_swap(buf, left_i, right_i, sizeof(int));
    quicksort_impl(buf, start, end);
  } else {
    // Otherwise we are done with this partition and we continue splitting
    // the array into 2 new partitions and sort them
    arr_swap(buf, left_i, end - 1, sizeof(int)); // swap left with pivot
    quicksort_impl(buf, start, left_i);
    quicksort_impl(buf, left_i + 1, end);
  }
}

/**
 * @brief Wrapper function around the actual implementation of the quicksort
 *        algorithm so that consumers don't need to specify the initial start
 *        value which is always zero
 *
 * @param buf     array to be sorted
 * @param bufsize size of the array to sort
 */
void quicksort(int buf[], int bufsize) { quicksort_impl(buf, 0, bufsize); }

/**
 * @brief Iterative implementation of selection sort
 *
 * @param buf     array to be sorted
 * @param bufsize size of the array to sort
 */
void selectionsort(int buf[], int bufsize) {
  // Index of smallest number seen in current iteration
  int min_i = 0;
  for (int i = 0; i < bufsize;) {
    for (int j = i; j < bufsize; ++j) {
      if (buf[j] < buf[min_i]) {
        min_i = j;
      }
    }
    arr_swap(buf, min_i, i, sizeof(int));
    min_i = ++i;
  }
}
