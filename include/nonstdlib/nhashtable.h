#pragma once

#include <stddef.h>
#include <stdint.h>

#include "nstring.h"

typedef struct {
  string_t *key;
  void *value;
  uint32_t hash; // So we don't need to resize when expanding
} ht_entry_t;

typedef struct {
  ht_entry_t **entries;
  size_t size;
  size_t capacity;
} ht_t;

uint32_t ht_hash(const string_t *key);
void *ht_get(const ht_t *table, const string_t *key);
ht_t *ht_init(size_t init_size);
void ht_expand(ht_t *table);
void ht_free(ht_t *table);
void ht_print(const ht_t *table);
void ht_put(ht_t *table, string_t *key, void *value);
