#pragma once

#include <stddef.h>

void  arr_swap(void *arr, int i, int j, size_t arr_type_size);
void  arr_reverse(void *arr, size_t arr_size, size_t arr_type_size);
void  arr_clear(void *arr, size_t arr_size);
void  arr_append(void *arr, size_t arr_size, void *val);
void  arr_remove(void *arr, size_t arr_size, void *val);
void *arr_pop(void *arr, size_t arr_size);
int   arr_contains(void *arr, size_t arr_size, void *val, size_t arr_type_size);
