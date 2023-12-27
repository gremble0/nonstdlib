#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "hashtable.h"

// TODO: fix increasing table size when table grows, what to do when hash() % max_size changes?
// TODO: generalize to support more types, unions?
// TODO: remove strlen calls

/**
 * djb2 hash function
 *
 * @return index into a hash table (needs to be %'d by table size)
 */
uint32_t hash(char *key) {
    uint32_t hash = 5381;

    for (size_t i = 0; i < strlen(key); ++i) {
        hash = hash * 33 + key[i];
    }

    return hash;
}

/**
 * @param init_size the initial size of the hash table, can be changed by ht_put
 * @return a malloc'd hash table
 */
ht_t *ht_init(uint32_t init_max_entries) {
    ht_t *new_ht = malloc(sizeof(ht_t));
    new_ht->n_entries = 0;
    new_ht->max_entries = init_max_entries;
    new_ht->entries = malloc(sizeof(htentry_t) * init_max_entries);

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
void ht_free(ht_t *table) {
    for (size_t i = 0; i < table->max_entries; ++i) {
        free(table->entries[i]);
    }

    free(table->entries);
    free(table);
}

/**
 * Doubles the size of a hash table
 *
 * @param table hash table to expand the size of
 */
void ht_expand(ht_t *table) {
    uint32_t prev_max_entries = table->max_entries;
    table->max_entries *= 2;
    table->entries = realloc(table->entries, sizeof(htentry_t) * table->max_entries);
    table->n_entries = 0; // Will be incremented in the loop by calling ht_put

    // Loop through table and reindex based on new size
    for (size_t i = 0; i < prev_max_entries; ++i) {
        if (table->entries[i] == NULL) {
            continue;
        }

        htentry_t *entry = table->entries[i];
        table->entries[i] = NULL; // TODO: memory management
        ht_put(table, entry->key, entry->value);
    }
}

void ht_print(ht_t *table) {
    for (size_t i = 0; i < table->max_entries; ++i) {
        if (table->entries[i] == NULL) {
            printf("[%zu]: --empty--\n", i);
        } else {
            htentry_t *entry = table->entries[i];
            printf("[%zu]: key: %s, value: %s\n", i, entry->key, entry->value);
        }
    }
}

char *ht_get(ht_t *table, char *key) {
    uint32_t index = hash(key) % table->max_entries;
    htentry_t *entry = table->entries[index];
    if (entry == NULL) {
        return NULL;
    }

    while (entry->key != key) {
        if (entry == NULL) {
            return NULL;
        }
        entry = table->entries[index++];
    }

    return entry->value;
}

void ht_put(ht_t *table, char *key, char *value) {
    if (table->n_entries + 1 > table->max_entries / 2) {
        ht_expand(table);
    }

    uint32_t hash_index = hash(key) % table->max_entries;
    htentry_t *existing_entry = table->entries[hash_index];

    if (existing_entry == NULL) {
        htentry_t *new_entry = malloc(sizeof(htentry_t));
        new_entry->key = key;
        new_entry->value = value;
        table->entries[hash_index] = new_entry;
        ++table->n_entries;
        return;
    }

    if (existing_entry->key == key) {
        existing_entry->value = value;
        return;
    }

    htentry_t *new_entry = malloc(sizeof(htentry_t));
    new_entry->key = key;
    new_entry->value = value;

    while (table->entries[++hash_index] != NULL) {}

    table->entries[hash_index] = new_entry;
    ++table->n_entries;
}
