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
    uint32_t *val = malloc(sizeof(uint32_t));
    *val = 4;
    stack_push(s, val);
    printf("%u\n", s->size);
    stack_pop(s);
    printf("%u\n", s->size);
}

int main() {
    // test_hashtable();
    test_stack();
}
