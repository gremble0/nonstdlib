#pragma once

#include <stdint.h>

typedef struct ht_entry {
    char *key;
    char *value;
    struct ht_entry *next;
} ht_entry;

typedef struct ht {
    ht_entry **entries;
    uint32_t n_entries;
    uint32_t max_entries;
} ht;


uint32_t hash(char *key, uint32_t key_size);
ht *ht_init(uint32_t init_size);
void ht_free(ht *table);
void ht_expand(ht *table);
void ht_print(ht *table);
char *ht_get(ht *table, char *key);
void ht_put(ht *table, char *key, char *value);
