#include <stdio.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable.h"
#include "nonstdlib/nlist.h"
#include "nonstdlib/nstring.h"

void test_demo(void) {
  // Small hashtable demo
  ht_t *table = ht_init(8);
  ht_put(table, &string_of("key"), &string_of("value"));

  const string_t *result = ht_get(table, &string_of("key"));
  ASSERT(result != NULL);
  ASSERT(string_compare(&string_of("value"), result) == 0);

  // Small list demo
  typedef struct {
    int x;
    char *s;
  } list_element;

  list_t *list = list_init(8);
  list_push_back(list, &(list_element){.x = 10, .s = "my list element"});

  const list_element *popped = list_pop_front(list);
  ASSERT(popped != NULL);
  ASSERT(popped->x == 10);
  ASSERT(strcmp(popped->s, "my list element") == 0);

  ht_free(table);
  list_free(list);

  printf("All assertions passed, library is working as expected :)\n");
}
