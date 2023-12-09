#include "hashtable.h"
#include <stdio.h>

int main() {
    ht *table = ht_init(1);
    ht_print(table);
    printf("---------------------\n");
    ht_put(table, "ASD", "yoyo");
    ht_print(table);
    printf("---------------------\n");
    ht_put(table, "ASD", "baba");
    ht_print(table);
    printf("---------------------\n");
    ht_put(table, "gogo", "yoyo");
    ht_print(table);
    printf("---------------------\n");
    ht_put(table, "popo", "yoyo");
    char *res = ht_get(table, "ASD");
    ht_print(table);
    ht_expand(table);
    printf("---------------------\n");
    ht_print(table);
    ht_free(table);
}
