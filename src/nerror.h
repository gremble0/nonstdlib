#pragma once

// TODO: goto catch??
#include <stddef.h>

#define ASSERT(expr)                                                           \
  do {                                                                         \
    if (!(expr)) {                                                             \
      err_assert_fail(#expr);                                                  \
    }                                                                          \
  } while (0)

void err_print_stacktrace();
_Noreturn void err_index_out_of_bounds(size_t index, size_t max_index);
_Noreturn void err_io_fail(const char *file_path);
_Noreturn void err_malloc_fail();
_Noreturn void err_pop_from_empty_linked_list();
_Noreturn void err_pop_from_empty_list();
_Noreturn void err_assert_fail(const char *expr);
