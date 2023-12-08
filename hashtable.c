#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hashtable.h"

// TODO: fix increasing table size when table grows, what to do when hash() % max_size changes?

/**
 * djb2 hash function
 *
 * @return index into a hash table
 */
uint32_t hash(uint8_t *key, uint32_t key_size) {
    uint32_t hash = 5381;

    for (size_t i = 0; i < key_size; ++i) {
        hash = hash * 33 + key[i];
    }

    return hash;
}

/**
 * @param init_size the initial size of the hash table, can be changed by ht_put
 * @return a malloc'd hash table with
 */
ht *ht_init(uint32_t init_size) {
    ht *new_ht = (ht*)malloc(sizeof(ht));
    new_ht->n_entries = 0;
    new_ht->max_size = init_size;

    for (size_t i = 0; i < init_size; ++i) {
        new_ht->entries[i] = malloc(sizeof(ht_entry));
    }

    return new_ht;
}

/**
 * frees memory allocated for hash table
 *
 * @param table table to free memory for
 */
void ht_free(ht *table) {
    for (size_t i = 0; i < table->max_size; ++i) {
        free(table->entries[i]);
    }

    free(table);
}
