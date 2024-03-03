#pragma once

// TODO: goto catch??
#include <stddef.h>
#include <stdnoreturn.h>

_Noreturn void err_index_out_of_bounds(size_t index, size_t max_index);
_Noreturn void err_io_fail(const char *file_path);
_Noreturn void err_malloc_fail();
_Noreturn void err_pop_from_empty_linked_list();
_Noreturn void err_pop_from_empty_list();
