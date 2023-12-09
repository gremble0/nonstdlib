#include "hashtable.h"

int main() {
    ht *table = ht_init(10000);
    ht_put(table, "ASD", "yoyo");
    char *res = ht_get(table, "ASD");
    ht_free(table);
}
