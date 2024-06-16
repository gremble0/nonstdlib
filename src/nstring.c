#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nstring.h"

/**
 * @brief Deep copy `str` into an identical `string_t`
 *
 * @param str string to copy
 * @return copied string
 */
string_t *string_dup(const string_t *str) {
  string_t *copied = malloc(sizeof(*copied));
  if (copied == NULL)
    err_malloc_fail();

  copied->s = strndup(str->s, str->len);
  copied->len = str->len;

  return copied;
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
 * @param len amount of bytes to copy into `str`
 */
void string_set(string_t *str, const char *s, size_t len) {
  free(str->s); // This is safe because free(NULL) is a no-op
  str->s = malloc(len * sizeof(char));
  if (str->s == NULL)
    err_malloc_fail();

  str->len = len;
  memcpy(str->s, s, len);
}

/**
 * @brief Append the string in `src` onto `dest` in place
 *
 * @param dest the string to append onto
 * @param src the string to append from
 */
void string_append(string_t *dest, const string_t *src) {
  dest->s = realloc(dest->s, dest->len + src->len + 1);
  if (dest->s == NULL)
    err_malloc_fail();

  // Strings must be null terminated, if not we have to do a lot of checks
  // everywhere and things get really messy.
  ASSERT(dest->s[dest->len] == '\0');
  ASSERT(src->s[src->len] == '\0');

  memcpy(dest->s + dest->len, src->s, src->len);
  dest->len += src->len;
  dest->s[dest->len] = '\0'; // Could copy src->len + 1, but this is clearer
}

/**
 * @brief Append a character to the end of a string
 *
 * @param dest the string to append onto
 * @param c the character to append
 */
void string_append_c(string_t *dest, char c) {
  dest->s = realloc(dest->s, dest->len + sizeof(c) + 1);
  if (dest->s == NULL)
    err_malloc_fail();

  ASSERT(dest->s[dest->len] == '\0');

  dest->s[dest->len] = c;
  dest->s[++dest->len] = '\0';
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
