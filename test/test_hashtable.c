#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "hashtable.h"
#include "test.h"

static int tests_passed = 0;
static int tests_ran = 0;

void test_hashtable(void) {
  TEST_MODULE_START("hash table");

  ht_t *table = ht_init(5);
  ht_put(table, "asd", "YOYO");
  assert(table->n_entries == 1);
  ht_put(table, "asd", "YAYA");
  assert(table->n_entries == 1);
  ht_put(table, "qwerty", "123");
  assert(table->n_entries == 2);
  ht_put(table, "qwertz", "BABA");
  assert(table->n_entries == 3);
  ht_put(table, "qwertyb", "POPO");
  assert(table->n_entries == 4);

  assert(strcmp(ht_get(table, "asd"), "YAYA") == 0);
  assert(strcmp(ht_get(table, "qwerty"), "123") == 0);
  assert(strcmp(ht_get(table, "qwertz"), "BABA") == 0);
  assert(table->max_entries == 10);

  ht_put(table,
         "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfjlaksdjfkd\
ajsdklfaskldfkasjldhfkljashdfklahsdfklhasdkljfhasdkjlhfkjlashdfkljashdfkljhasdklfhkk\
ajsdhfkjlahsdkjflhaskldfhkljasdfkjasdfkashfklahsdkfljhaskljdhkajlshdfkjlahsdkljhakld\
sdhfkjlashdfkljhakjsldjashdfklalskdflkfhqwoliefhuqiowefiwlfiwelaufrawilerfilwhrfiklu\
hfruilwehrfiluaweriulhweuirlhweiurhuweuiruhiweuhruqwueirlweihfilweufqwelfhiuweihrqlw\
iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirluhqwuierhqwelrihqweirulhqwieurh",
         "POPO");
  assert(table->n_entries == 5);
  ht_put(table, "",
         "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfjlaksdjfkd\
ajsdklfaskldfkasjldhfkljashdfklahsdfklhasdkljfhasdkjlhfkjlashdfkljashdfkljhasdklfhkk\
ajsdhfkjlahsdkjflhaskldfhkljasdfkjasdfkashfklahsdkfljhaskljdhkajlshdfkjlahsdkljhakld\
sdhfkjlashdfkljhakjsldjashdfklalskdflkfhqwoliefhuqiowefiwlfiwelaufrawilerfilwhrfiklu\
hfruilwehrfiluaweriulhweuirlhweiurhuweuiruhiweuhruqwueirlweihfilweufqwelfhiuweihrqlw\
iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirluhqwuierhqwelrihqweirulhqwieurh");
  assert(table->n_entries == 6);
  assert(table->max_entries == 20);

  long a = 2;
  ht_put(table, "jig", &a);
  assert(*(long *)ht_get(table, "jig") == 2);
  assert(ht_get(table, "doesnt_exist") == NULL);

  ht_free(table);

  TEST_FUNCTION_SUCCESS("hash table all");
  TEST_MODULE_END("hash table");
}
