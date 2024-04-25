#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nstring.h"

string_t *string_of(const char *s, size_t s_len) {
  string_t *str = malloc(sizeof(*str));
  if (str == NULL)
    err_malloc_fail();

  str->s = malloc(s_len * sizeof(char));
  memcpy(str->s, s, s_len);
  str->len = s_len;

  return str;
}

void string_clear(string_t *str) {
  str->s = realloc(str->s, 0);
  str->s = NULL;
  str->len = 0;
}

void string_set(string_t *str, const char *s, size_t s_len) {
  str->s = realloc(str->s, s_len * sizeof(char));
  if (str->s == NULL)
    err_malloc_fail();

  memcpy(str->s, s, s_len);
}

void string_free(string_t *string) {
  free(string->s);
  free(string);
}
