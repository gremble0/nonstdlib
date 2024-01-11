#pragma once

#include <stdint.h>

typedef struct ht_entry {
    const char *key;
    const char *value;
} ht_entry_t;

typedef struct ht_t {
    ht_entry_t **entries;
    uint32_t n_entries;
    uint32_t max_entries;
} ht_t;

ht_t *ht_init(uint32_t init_size);
void ht_free(ht_t *table);

const char *ht_get(ht_t *table, const char *key);
void ht_put(ht_t *table, const char *key, const char *value);
void ht_print(ht_t *table);

uint32_t hash(const char *key);
void ht_expand(ht_t *table);
