#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nstring.h"

/**
 * @brief Make a `string_t` by copying `s_len` bytes from `s`
 *
 * @param s string to copy
 * @param s_len amount of bytes to copy from `s`
 * @return malloc'd `string_t`
 */
string_t *string_of(const char *s, size_t s_len) {
  string_t *str = malloc(sizeof(*str));
  if (str == NULL)
    err_malloc_fail();

  str->s = malloc(s_len * sizeof(char));
  memcpy(str->s, s, s_len);
  str->len = s_len;

  return str;
}

/**
 * @brief Compare two strings.
 *
 * @param str1 first string to compare
 * @param str2 second string to compare
 * @return 0 if the strings are equal, -1 if they have different length or if
 * the first string is lexicographically larger than str2. 1 if str2 is
 * lexicographically larger than s1.
 * @see `strcmp`
 */
int string_compare(const string_t *str1, const string_t *str2) {
  if (str1 == str2)
    return 0;
  else if (str1->len != str2->len)
    return -1;

  for (size_t i = 0; i < str1->len; ++i)
    if (str1->s[i] != str2->s[i])
      return str1->s[i] > str2->s[i] ? -1 : 1;

  return 0;
}

/**
 * @brief Clear the contents of a string
 *
 * @param str string to clear
 */
void string_clear(string_t *str) {
  free(str->s);
  str->s = NULL;
  str->len = 0;
}

/**
 * @brief Copy the contents of `s` into `str`, clearing the existing string
 *
 * @param str string to write to
 * @param s string to copy into `str`
 * @param s_len amount of bytes to copy into `str`
 */
void string_set(string_t *str, const char *s, size_t s_len) {
  free(str->s); // This is safe because free(NULL) is a no-op
  str->s = malloc(s_len * sizeof(char));
  if (str->s == NULL)
    err_malloc_fail();

  str->len = s_len;
  memcpy(str->s, s, s_len);
}

/**
 * @brief Free all data associated with a string
 *
 * @param string string to free
 */
void string_free(string_t *string) {
  free(string->s);
  free(string);
}
