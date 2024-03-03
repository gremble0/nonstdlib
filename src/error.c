#include <execinfo.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "error.h"

static void err_print_stacktrace() {
  void *callstack[128];
  int frames = backtrace(callstack, 128);
  char **strs = backtrace_symbols(callstack, frames);

  fprintf(stderr, "Running stacktrace:\n");
  for (int i = 0; i < frames; ++i) {
    fprintf(stderr, "%s\n", strs[i]);
  }

  free(strs);
}

_Noreturn void err_custom(const char *errormsg, ...) {
  err_print_stacktrace();

  va_list args;
  va_start(args, errormsg);
  vfprintf(stderr, errormsg, args);
  va_end(args);

  exit(1);
}

_Noreturn void err_io_fail(const char *file_path) {
  err_custom("ERROR_IO_FAIL: error doing IO to file at '%s'\n", file_path);
}

_Noreturn void err_index_out_of_bounds(size_t index, size_t max_index) {
  err_custom(
      "ERROR_INDEX_OUT_OF_BOUNDS: index %zu out of bounds where max_index "
      "is %zu\n",
      index, max_index);
}

_Noreturn void err_malloc_fail() {
  err_custom("ERROR_MALLOC_FAIL: Failed to allocate memory\n");
}

_Noreturn void err_pop_from_empty_list() {
  err_custom("ERROR_POP_FROM_EMPTY_LIST: Cannot pop from empty list\n");
}
