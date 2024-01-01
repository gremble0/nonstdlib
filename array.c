#include <string.h>

#include "array.h"

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
