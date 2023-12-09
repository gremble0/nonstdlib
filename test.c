#include "hashtable.h"

int main() {
    ht *table = ht_init(40);
    ht_put(table, "ASD", "yoyo");
    ht_put(table, "ASD", "baba");
    ht_put(table, "gogo", "yoyo");
    ht_put(table, "popo", "yoyo");
    char *res = ht_get(table, "ASD");
    ht_print(table);
    ht_free(table);
}
