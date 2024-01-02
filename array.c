#include <string.h>

#include "array.h"

void arr_swap(void *arr, int i, int j, size_t arr_type_size) {
    char *a = (char*)arr;
    char temp[arr_type_size];

    // TODO: maybe do this ourselves instead of using string.h
    // Copy contents of a[i] into temporary buffer
    memcpy(temp, a + i, arr_type_size);
    // Copy a[j] into a[i]
    memcpy(a + i * arr_type_size, a + j * arr_type_size, arr_type_size);
    // Copy contents of temp into a[j]
    memcpy(a + j * arr_type_size, temp, arr_type_size);
}

void arr_reverse(void *arr, size_t arr_size, size_t arr_type_size) {
    for (size_t i = 0; i < arr_size / 2; ++i) {
        arr_swap(arr, i, arr_size - 1 - i, arr_type_size);
    }
}

int arr_contains(void *arr, size_t arr_size, void *val, size_t arr_type_size) {
    // Cast void* to single byte pointers so we can multiply it by val_type_size
    char *a = (char*)arr;
    char *v = (char*)val;

    for (size_t i = 0; i < arr_size; ++i) {
        // TODO: maybe do this ourselves instead of using string.h
        // Move i * val_type_size and compare val_type_size bytes each iteration
        // We have to do it like this because "generics" in C is quite janky
        if (memcmp(&a[i * arr_type_size], v, arr_type_size) == 0) {
            return 1;
        }
    }

    return 0;
}
