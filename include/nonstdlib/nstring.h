#pragma once

#include <stddef.h>

typedef struct {
  char *s; // NULL terminated
  size_t len;
} string_t;

// Shortcut for making string_t structs from string literals or (null
// terminated) char arrays - NOTE: does not work for char pointers
#define string_of(slit)                                                        \
  (string_t) { slit, sizeof(slit) - 1 }

string_t *string_dup(const string_t *str);
int string_compare(const string_t *s1, const string_t *s2);
void string_clear(string_t *str);
void string_free(string_t *str);
void string_set(string_t *str, const char *s, size_t len);
void string_append(string_t *dest, const string_t *src);
void string_append_c(string_t *dest, char c);
