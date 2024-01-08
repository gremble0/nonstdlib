#include <string.h>

#include "array.h"

/**
 * @param arr           array to swap elements in
 * @param i             index into arr of first element to swap
 * @param j             index into arr of second element to swap
 * @param arr_type_size amount of bytes used for each element in arr
 */
void arr_swap(void *arr, int i, int j, size_t arr_type_size) {
    char temp[arr_type_size];

    // TODO: maybe do this ourselves instead of using string.h
    // Copy contents of a[i] into temporary buffer
    memcpy(temp, arr + i * arr_type_size, arr_type_size);
    // Copy a[j] into a[i]
    memcpy(arr + i * arr_type_size, arr + j * arr_type_size, arr_type_size);
    // Copy contents of temp into a[j]
    memcpy(arr + j * arr_type_size, temp, arr_type_size);
}

/**
 * @param arr           array to reverse
 * @param arr_size      size of arr
 * @param arr_type_size amount of bytes used for each element in arr
 */
void arr_reverse(void *arr, size_t arr_size, size_t arr_type_size) {
    for (size_t i = 0; i < arr_size / 2; ++i) {
        arr_swap(arr, i, arr_size - 1 - i, arr_type_size);
    }
}

/**
 * @param arr           array to check in
 * @param arr_size      size of arr
 * @param val           value to check if exists in arr
 * @param arr_type_size amount of bytes used for each element in arr
 * @return              1 if arr contains val 0 if not
 */
int arr_contains(void *arr, size_t arr_size, void *val, size_t arr_type_size) {
    for (size_t i = 0; i < arr_size; ++i) {
        // TODO: maybe do this ourselves instead of using string.h
        // Move i * val_type_size and compare val_type_size bytes each iteration
        // We have to do it like this because "generics" in C is quite janky
        if (memcmp(&arr[i * arr_type_size], val, arr_type_size) == 0) {
            return 1;
        }
    }

    return 0;
}
