#pragma once

#include <stddef.h>

typedef struct {
  char *key;
  void *value;
} ht_entry_t;

typedef struct {
  ht_entry_t **entries;
  size_t n_entries;
  size_t max_entries;
} ht_t;

void *ht_get(const ht_t *table, const char *key, size_t key_size);
ht_t *ht_init(size_t init_size);
void ht_expand(ht_t *table);
void ht_free(ht_t *table);
void ht_print(const ht_t *table);
void ht_put(ht_t *table, const char *key, size_t key_size, const void *value,
            size_t value_size);
