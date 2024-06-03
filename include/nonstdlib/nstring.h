#pragma once

#include <stddef.h>

typedef struct {
  char *s; // Should not be NULL terminated
  size_t len;
} string_t;

#define string_of_lit(lit) string_of(lit, sizeof(lit))
#define string_append_lit(dest, lit) string_append(dest, &(string_t){lit, sizeof(lit)})

string_t *string_of(const char *s, size_t len);
string_t *string_copy(const string_t *str);
int string_compare(const string_t *s1, const string_t *s2);
void string_clear(string_t *str);
void string_free(string_t *str);
void string_set(string_t *str, const char *s, size_t len);
void string_append(string_t *dest, string_t *src);
void string_append_c(string_t *dest, char c);
