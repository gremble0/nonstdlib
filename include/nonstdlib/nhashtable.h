#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct {
  char *key;
  void *value;
} ht_entry_t;

typedef struct {
  ht_entry_t **entries;
  size_t cur_size;
  size_t max_size;
} ht_t;

uint32_t ht_hash(const char *key, size_t key_size);
void *ht_get(const ht_t *table, const char *key, size_t key_size);
ht_t *ht_init(size_t init_size);
void ht_expand(ht_t *table);
void ht_free(ht_t *table);
void ht_print(const ht_t *table);
void ht_put(ht_t *table, char *key, size_t key_size, void *value);
