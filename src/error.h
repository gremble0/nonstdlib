#pragma once

// TODO: goto catch??
#include <stddef.h>

void err_index_out_of_bounds(size_t index, size_t max_index);
void err_malloc_fail();
void err_pop_from_empty_list();
