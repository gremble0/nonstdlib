#pragma once

#include <stddef.h>

typedef struct {
  char *s; // Should not be NULL terminated
  size_t len;
} string_t;

string_t *string_of(const char *s, size_t s_len);
int string_compare(const string_t *s1, const string_t *s2);
void string_clear(string_t *str);
void string_free(string_t *str);
void string_set(string_t *str, const char *s, size_t s_len);
void string_append(string_t *dest, string_t *src);
