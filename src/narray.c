#include <string.h>

#include "nonstdlib/narray.h"

/**
 * @brief Check if value is present in array
 *
 * @param arr array to check in
 * @param arr_size size/length of arr
 * @param val value to check if exists in arr
 * @param type_size amount of bytes used for each element in arr
 * @return 1 if arr contains val 0 if not
 */
int arr_contains(const void *arr, size_t arr_size, const void *val,
                 size_t type_size) {
  for (size_t i = 0; i < arr_size; ++i)
    // Move i * val_type_size and compare val_type_size bytes each iteration
    if (memcmp(&arr[i * type_size], val, type_size) == 0)
      return 1;

  return 0;
}

/**
 * @brief Checks if all elements in two arrays are equal
 *
 * @param arr1 first array to compare
 * @param arr1_size size/length of arr1
 * @param arr2 second array to compare
 * @param arr2_size size/length of arr2
 * @param type_size amount of bytes used for each element in arr1 and arr2
 * @return 1 if arrays are equal 0 if not
 */
int arr_equals(const void *arr1, size_t arr1_size, const void *arr2,
               size_t arr2_size, size_t type_size) {
  if (arr1_size != arr2_size)
    return 0;

  for (size_t i = 0; i < arr1_size; ++i)
    if (memcmp(&arr1[i * type_size], &arr2[i * type_size], type_size) != 0)
      return 0;

  return 1;
}

/**
 * @brief Clear the array by filling it with 0s
 *
 * @param arr array to clear
 * @param arr_size size/length of arr
 * @param type_size amount of bytes used for each element in arr
 */
void arr_clear(void *arr, size_t arr_size, size_t type_size) {
  memset(arr, 0, type_size * arr_size);
}

/**
 * @brief Reverse the array in place
 *
 * @param arr array to reverse
 * @param arr_size size/length of arr
 * @param type_size amount of bytes used for each element in arr
 */
void arr_reverse(void *arr, size_t arr_size, size_t type_size) {
  for (size_t i = 0; i < arr_size / 2; ++i)
    arr_swap(arr, i, arr_size - 1 - i, type_size);
}

/**
 * @brief Swap elements at index i and j within an array
 *
 * @param arr array to swap elements in
 * @param i index into arr of first element to swap
 * @param j index into arr of second element to swap
 * @param type_size amount of bytes used for each element in arr
 */
void arr_swap(void *arr, int i, int j, size_t type_size) {
  char temp[type_size];

  // Copy contents of a[i] into temporary buffer
  memcpy(temp, arr + i * type_size, type_size);
  // Copy a[j] into a[i]
  memcpy(arr + i * type_size, arr + j * type_size, type_size);
  // Copy contents of temp into a[j]
  memcpy(arr + j * type_size, temp, type_size);
}
