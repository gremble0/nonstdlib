#pragma once

// TODO: goto catch??
#include <stddef.h>
#include <stdnoreturn.h>

// TODO: only have err_custom here, define other errors statically where they
// are used, also maybe change err_custom to not print backtrace for the error
// functions
_Noreturn void err_custom(const char *errmsg, ...);
_Noreturn void err_index_out_of_bounds(size_t index, size_t max_index);
_Noreturn void err_io_fail(const char *file_path);
_Noreturn void err_malloc_fail();
_Noreturn void err_pop_from_empty_linked_list();
_Noreturn void err_pop_from_empty_list();
