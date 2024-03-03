#pragma once

// TODO: goto catch??
// Some kind of inheritance for error handling
#ifdef __GLIBC__
#include <execinfo.h>
#define ERROR(type, errstr, ...)                                               \
  do {                                                                         \
    fprintf(stderr, "Running stacktrace:\n");                                  \
    void *callstack[128];                                                      \
    int i, frames = backtrace(callstack, 128);                                 \
    char **strs = backtrace_symbols(callstack, frames);                        \
    for (i = 0; i < frames; ++i) {                                             \
      printf("%s\n", strs[i]);                                                 \
    }                                                                          \
    free(strs);                                                                \
    fprintf(stderr, type ": " errstr "\n", ##__VA_ARGS__);                     \
    exit(1);                                                                   \
  } while (0)
#else
#define ERROR(type, errstr, ...)                                               \
  do {                                                                         \
    fprintf(stderr, "%s:%d: " type ": " errstr "\n", __FILE__, __LINE__,       \
            ##__VA_ARGS__);                                                    \
    exit(1);                                                                   \
  } while (0)
#endif

#define ERROR_MALLOC_FAIL()                                                    \
  ERROR("ERROR_MALLOC_FAIL", "Memory allocation returned NULL");

#define ERROR_INDEX_OUT_OF_BOUNDS(index, max_index)                            \
  ERROR("ERROR_INDEX_OUT_OF_BOUNDS",                                           \
        "index %zu out of bounds where max_index is %zu", index, max_index);

#define ERROR_POP_FROM_EMPTY_LIST()                                            \
  ERROR("ERROR_POP_FROM_EMPTY_LIST", "cannot pop from empty list");
