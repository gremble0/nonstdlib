#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
  char *key;
  void *value;
} ht_entry_t;

typedef struct {
  ht_entry_t **entries;
  uint32_t n_entries;
  uint32_t max_entries;
} ht_t;

void *ht_get(const ht_t *table, const char *key);
ht_t *ht_init(uint32_t init_size);
void ht_expand(ht_t *table);
void ht_free(ht_t *table);
void ht_print(const ht_t *table);
void ht_put(ht_t *table, const char *key, const void *value, size_t value_size);
