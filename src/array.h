#pragma once

#include <stddef.h>

// These functions work on basic C types without using structs
// For a more dynamic data structure use lists from list.h
void arr_clear(void *arr, size_t arr_size, size_t arr_type_size);
int  arr_contains(void *arr, size_t arr_size, void *val, size_t arr_type_size);
void arr_reverse(void *arr, size_t arr_size, size_t arr_type_size);
void arr_swap(void *arr, int i, int j, size_t arr_type_size);
