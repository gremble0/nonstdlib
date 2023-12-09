#include <stdio.h>
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
uint32_t hash(char *key, uint32_t key_size) {
    uint32_t hash = 5381;

    for (size_t i = 0; i < key_size; ++i) {
        hash = hash * 33 + key[i];
    }

    return hash;
}

/**
 * @param init_size the initial size of the hash table, can be changed by ht_put
 * @return a malloc'd hash table
 */
ht *ht_init(uint32_t init_max_entries) {
    ht *new_ht = malloc(sizeof(ht));
    new_ht->n_entries = 0;
    new_ht->max_entries = init_max_entries;
    new_ht->entries = malloc(sizeof(ht_entry *) * init_max_entries);

    for (size_t i = 0; i < init_max_entries; ++i) {
        new_ht->entries[i] = NULL;
    }

    return new_ht;
}

/**
 * frees memory allocated for hash table
 *
 * @param table table to free memory for
 */
void ht_free(ht *table) {
    for (size_t i = 0; i < table->max_entries; ++i) {
        free(table->entries[i]);
    }

    free(table->entries);
    free(table);
}

void ht_print(ht *table) {
    for (size_t i = 0; i < table->max_entries; ++i) {
        printf("[%zu]: key: %s, value: %s\n", i, table->entries[i]->key, table->entries[i]->value);
    }
}

char *ht_get(ht *table, char *key) {
    ht_entry *entry = table->entries[hash(key, strlen(key)) % table->max_entries];
    if (entry == NULL) {
        return NULL;
    }

    while (entry->key != key) {
        if (entry == NULL) {
            return NULL;
        }
        entry = entry->next;
    }

    return entry->value;
}

void ht_put(ht *table, char *key, char *value) {
    uint32_t hash_index = hash(key, strlen(key)) % table->max_entries;
    ht_entry *existing_entry = table->entries[hash_index];
    if (existing_entry != NULL) {
        existing_entry->value = value;
    } else {
        ht_entry *new_entry = malloc(sizeof(ht_entry*));
        new_entry->key = key;
        new_entry->value = value;
        table->entries[hash_index] = new_entry;
    }
}
