#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

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

void err_index_out_of_bounds(size_t index, size_t max_index) {
  err_print_stacktrace();
  fprintf(stderr,
          "ERROR_INDEX_OUT_OF_BOUNDS: index %zu out of bounds where max_index "
          "is %zu\n",
          index, max_index);

  exit(1);
}

void err_malloc_fail() {
  err_print_stacktrace();
  fprintf(stderr, "ERROR_MALLOC_FAIL: Failed to allocate memory\n");

  exit(1);
}

void err_pop_from_empty_list() {
  err_print_stacktrace();
  fprintf(stderr, "ERROR_POP_FROM_EMPTY_LIST: Cannot pop from empty list\n");

  exit(1);
}
