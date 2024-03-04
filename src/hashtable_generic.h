#pragma once

#define ht_prototype(type)                                                     \
  typedef struct type##_ht_entry_t {                                           \
    const char *key;                                                           \
    const type *value;                                                         \
  } type##_ht_entry_t;                                                         \
                                                                               \
  typedef struct type##_ht_t {                                                 \
    type##_ht_entry_t **entries;                                               \
    uint32_t n_entries;                                                        \
    uint32_t max_entries;                                                      \
  } type##_ht_t;                                                               \
                                                                               \
  const type *type##_ht_get(type##_ht_t *table, const char *key);              \
  type##_ht_t *type##_ht_init(uint32_t init_size);                             \
  uint32_t type##_hash(const char *key);                                       \
  void type##_ht_expand(type##_ht_t *table);                                   \
  void type##_ht_free(type##_ht_t *table);                                     \
  void type##_ht_put(type##_ht_t *table, const char *key, const type *value);

#define ht_impl(type)                                                          \
  static void type##_ht_update_entry(type##_ht_t *table,                       \
                                     size_t old_hash_index) {                  \
    type##_ht_entry_t *entry = table->entries[old_hash_index];                 \
    uint32_t new_hash_index = type##_hash(entry->key) % table->max_entries;    \
    if (new_hash_index == old_hash_index) {                                    \
      return;                                                                  \
    }                                                                          \
                                                                               \
    table->entries[old_hash_index] = NULL;                                     \
    while (table->entries[++new_hash_index] != NULL)                           \
      ;                                                                        \
                                                                               \
    table->entries[new_hash_index] = entry;                                    \
  }                                                                            \
                                                                               \
  const type *type##_ht_get(type##_ht_t *table, const char *key) {             \
    uint32_t index = type##_hash(key) % table->max_entries;                    \
    type##_ht_entry_t *entry = table->entries[index];                          \
    if (entry == NULL) {                                                       \
      return NULL;                                                             \
    }                                                                          \
                                                                               \
    while (entry->key != key) {                                                \
      entry = table->entries[index++];                                         \
      if (entry == NULL) {                                                     \
        return NULL;                                                           \
      }                                                                        \
    }                                                                          \
                                                                               \
    return entry->value;                                                       \
  }                                                                            \
                                                                               \
  type##_ht_t *type##_ht_init(uint32_t init_max_entries) {                     \
    type##_ht_t *new_ht = malloc(sizeof(type##_ht_t));                         \
    if (new_ht == NULL) {                                                      \
      return NULL;                                                             \
    }                                                                          \
                                                                               \
    new_ht->n_entries = 0;                                                     \
    new_ht->max_entries = init_max_entries;                                    \
    new_ht->entries = malloc(sizeof(type##_ht_entry_t) * init_max_entries);    \
    if (new_ht->entries == NULL) {                                             \
      free(new_ht);                                                            \
      return NULL;                                                             \
    }                                                                          \
                                                                               \
    for (size_t i = 0; i < init_max_entries; ++i) {                            \
      new_ht->entries[i] = NULL;                                               \
    }                                                                          \
                                                                               \
    return new_ht;                                                             \
  }                                                                            \
                                                                               \
  uint32_t type##_hash(const char *key) {                                      \
    uint32_t hash = 5381;                                                      \
                                                                               \
    for (size_t i = 0; i < strlen(key); ++i) {                                 \
      hash = hash * 33 + key[i];                                               \
    }                                                                          \
                                                                               \
    return hash;                                                               \
  }                                                                            \
                                                                               \
  void type##_ht_expand(type##_ht_t *table) {                                  \
    uint32_t prev_max_entries = table->max_entries;                            \
    table->max_entries *= 2;                                                   \
    table->entries = realloc(table->entries,                                   \
                             sizeof(type##_ht_entry_t) * table->max_entries);  \
                                                                               \
    for (size_t i = 0; i < prev_max_entries; ++i) {                            \
      if (table->entries[i] == NULL) {                                         \
        continue;                                                              \
      }                                                                        \
      type##_ht_update_entry(table, i);                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  void type##_ht_free(type##_ht_t *table) {                                    \
    for (size_t i = 0; i < table->max_entries; ++i) {                          \
      free(table->entries[i]);                                                 \
    }                                                                          \
                                                                               \
    free(table->entries);                                                      \
    free(table);                                                               \
  }                                                                            \
                                                                               \
  void type##_ht_print(type##_ht_t *table) {                                   \
    for (size_t i = 0; i < table->max_entries; ++i) {                          \
      if (table->entries[i] == NULL) {                                         \
        printf("[%zu]: --empty--\n", i);                                       \
      } else {                                                                 \
        type##_ht_entry_t *entry = table->entries[i];                          \
        printf("[%zu]: key: %s, value: %p\n", i, entry->key, entry->value);    \
      }                                                                        \
    }                                                                          \
  }                                                                            \
                                                                               \
  void type##_ht_put(type##_ht_t *table, const char *key, const type *value) { \
    if (table->n_entries + 1 > table->max_entries / 2) {                       \
      type##_ht_expand(table);                                                 \
    }                                                                          \
                                                                               \
    type##_ht_entry_t *new_entry = malloc(sizeof(type##_ht_entry_t));          \
    if (new_entry == NULL) {                                                   \
      err_malloc_fail();                                                       \
    }                                                                          \
    new_entry->key = key;                                                      \
    new_entry->value = value;                                                  \
                                                                               \
    uint32_t hash_index = type##_hash(key) % table->max_entries;               \
    type##_ht_entry_t *existing_entry = table->entries[hash_index];            \
                                                                               \
    if (existing_entry == NULL) {                                              \
      table->entries[hash_index] = new_entry;                                  \
      ++table->n_entries;                                                      \
      return;                                                                  \
    }                                                                          \
                                                                               \
    if (existing_entry->key == key) {                                          \
      free(existing_entry);                                                    \
      table->entries[hash_index] = new_entry;                                  \
      return;                                                                  \
    }                                                                          \
                                                                               \
    while (table->entries[++hash_index] != NULL)                               \
      ;                                                                        \
                                                                               \
    table->entries[hash_index] = new_entry;                                    \
    ++table->n_entries;                                                        \
  }\
