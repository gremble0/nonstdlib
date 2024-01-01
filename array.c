#include <string.h>

#include "array.h"

void arr_swap(int buf[], int i, int j) {
    int at_i = buf[i];
    buf[i] = buf[j];
    buf[j] = at_i;
}

void arr_reverse(void *arr, size_t arr_size) {
    for (size_t i = 0; i < arr_size / 2; ++i) {
        arr_swap(arr, i, arr_size - 1 - i);
    }
}

int arr_contains(void *arr, size_t arr_size, void *val, size_t val_type_size) {
    // Cast void* to single byte pointers so we can multiply it by val_type_size
    char *a = (char*)arr;
    char *v = (char*)val;

    for (size_t i = 0; i < arr_size; ++i) {
        // Move i * val_type_size and compare val_type_size bytes each iteration
        // We have to do it like this because "generics" in C is quite janky
        if (memcmp(&a[i * val_type_size], v, val_type_size) == 0) {
            return 1;
        }
    }

    return 0;
}
