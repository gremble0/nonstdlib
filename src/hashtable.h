#pragma once

#include <stdint.h>

typedef struct ht_entry {
    char *key;
    char *value;
} htentry_t;

typedef struct ht {
    htentry_t **entries;
    uint32_t n_entries;
    uint32_t max_entries;
} ht_t;

ht_t *ht_init(uint32_t init_size);
void ht_free(ht_t *table);

char *ht_get(ht_t *table, char *key);
void ht_put(ht_t *table, char *key, char *value);
void ht_print(ht_t *table);

uint32_t hash(char *key);
void ht_expand(ht_t *table);
