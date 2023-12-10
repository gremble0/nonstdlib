#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "hashtable.h"

void test_hashtable(void) {
    ht *table = ht_init(5);
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

    ht_put(table, "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfjlaksdjfkd\
ajsdklfaskldfkasjldhfkljashdfklahsdfklhasdkljfhasdkjlhfkjlashdfkljashdfkljhasdklfhkk\
ajsdhfkjlahsdkjflhaskldfhkljasdfkjasdfkashfklahsdkfljhaskljdhkajlshdfkjlahsdkljhakld\
sdhfkjlashdfkljhakjsldjashdfklalskdflkfhqwoliefhuqiowefiwlfiwelaufrawilerfilwhrfiklu\
hfruilwehrfiluaweriulhweuirlhweiurhuweuiruhiweuhruqwueirlweihfilweufqwelfhiuweihrqlw\
iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirluhqwuierhqwelrihqweirulhqwieurh", "POPO");
    assert(table->n_entries == 5);
    ht_put(table, "", "qwertyblajsdflkjasdkljfklasjdfkjalskdfjlkasjdflkjaslkdfjlaksdjfkd\
ajsdklfaskldfkasjldhfkljashdfklahsdfklhasdkljfhasdkjlhfkjlashdfkljashdfkljhasdklfhkk\
ajsdhfkjlahsdkjflhaskldfhkljasdfkjasdfkashfklahsdkfljhaskljdhkajlshdfkjlahsdkljhakld\
sdhfkjlashdfkljhakjsldjashdfklalskdflkfhqwoliefhuqiowefiwlfiwelaufrawilerfilwhrfiklu\
hfruilwehrfiluaweriulhweuirlhweiurhuweuiruhiweuhruqwueirlweihfilweufqwelfhiuweihrqlw\
iuerbqnwlriujqwherilqwehrilquwehrilqwehrilqweirluhqwuierhqwelrihqweirulhqwieurh");
    assert(table->n_entries == 6);
    assert(table->max_entries == 20);
    ht_print(table);

    ht_free(table);
}

void test_stack(void) {
    stack *s = stack_init();

    uint32_t *val1 = malloc(sizeof(uint32_t));
    uint32_t *val2 = malloc(sizeof(uint32_t));
    uint32_t *val3 = malloc(sizeof(uint32_t));
    *val1 = 1;
    *val2 = 2;
    *val3 = 3;
    stack_push(s, val1);
    stack_push(s, val2);
    stack_push(s, val3);

    assert(s->size == 3);
    assert(*(uint32_t *)stack_get(s, 0) == 3);
    assert(*(uint32_t *)stack_get(s, 1) == 2);
    assert(*(uint32_t *)stack_get(s, 2) == 1);

    val1 = stack_pop(s);
    val2 = stack_pop(s);
    val3 = stack_pop(s);
    assert(*val1 == 3);
    assert(*val2 == 2);
    assert(*val3 == 1);
    assert(stack_pop(s) == NULL);

    free(val1);
    free(val2);
    free(val3);
    stack_free(s);
}

int main() {
    // test_hashtable();
    test_stack();
}
