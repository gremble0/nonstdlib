#include "quicksort.h"

/**
 * Wrapper function around the actual implementation of the quicksort algorithm
 * so that consumers don't need to specify the initial start value which is
 * always zero
 *
 * @param buf     array to be sorted
 * @param bufsize size of the array to sort
 */
void quicksort(int buf[], int bufsize) {
    quicksort_impl(buf, 0, bufsize);
}

/**
 * Recursive implementation of the quicksort algorithm
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

    int left_i = 0, right_i = end - 1;
    // Increment left_i until buf[left_i] is greater than pivot
    while (buf[left_i] < pivot) {
        left_i++;
    }

    // Increment right_i until buf[right_i] is less than pivot
    while (buf[right_i] > pivot) {
        right_i--;
    }

    if (left_i < right_i) {
        swap(buf, left_i, right_i);
        quicksort_impl(buf, start, end);
    } else {
        swap(buf, left_i, end - 1); // swap left with pivot
        quicksort_impl(buf, start, left_i);
        quicksort_impl(buf, left_i + 1, end);
    }
}

/**
 * Helper function to swap 2 elements in an array
 *
 * @param buf array to swap elements in
 * @param i   index of first element to swap
 * @param j   index of second element to swap
 */
void swap(int buf[], int i, int j) {
    int at_i = buf[i];
    buf[i] = buf[j];
    buf[j] = at_i;
}
