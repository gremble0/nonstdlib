#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "hashtable.h"

/**
 * @brief Get an element from a hash table
 *
 * @param table table to get from
 * @param key key to get
 * @return value of the given key
 */
const void *ht_get(ht_t *table, const char *key) {
  uint32_t index = hash(key) % table->max_entries;
  ht_entry_t *entry = table->entries[index];
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

/**
 * @brief Initialize an empty hash table allocated on the heap
 *
 * @param init_size the initial size of the hash table, can be changed by ht_put
 * @return a malloc'd hash table
 */
ht_t *ht_init(uint32_t init_max_entries) {
  ht_t *new_ht = malloc(sizeof(ht_t));
  if (new_ht == NULL) {
    return NULL;
  }

  new_ht->n_entries = 0;
  new_ht->max_entries = init_max_entries;
  new_ht->entries = malloc(sizeof(ht_entry_t) * init_max_entries);
  if (new_ht->entries == NULL) {
    free(new_ht);
    return NULL;
  }

  for (size_t i = 0; i < init_max_entries; ++i) {
    new_ht->entries[i] = NULL;
  }

  return new_ht;
}

/**
 * @brief djb2 hash function
 *
 * @return index into a hash table (needs to be %'d by table size)
 */
uint32_t hash(const char *key) {
  uint32_t hash = 5381;

  for (size_t i = 0; i < strlen(key); ++i) {
    hash = hash * 33 + key[i];
  }

  return hash;
}

/**
 * @brief Doubles the size of a hash table
 *
 * @param table hash table to expand the size of
 */
void ht_expand(ht_t *table) {
  uint32_t prev_max_entries = table->max_entries;
  table->max_entries *= 2;
  table->entries =
      realloc(table->entries, sizeof(ht_entry_t) * table->max_entries);
  table->n_entries = 0; // Will be incremented in the loop by calling ht_put

  // Loop through table and reindex based on new size
  for (size_t i = 0; i < prev_max_entries; ++i) {
    if (table->entries[i] == NULL) {
      continue;
    }

    ht_entry_t *entry = table->entries[i];
    table->entries[i] = NULL; // TODO: memory management
    ht_put(table, entry->key, entry->value);
  }
}

/**
 * @brief frees memory allocated for hash table
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
 * @brief Print contents of hash table
 *
 * @param table table to print
 */
void ht_print(ht_t *table) {
  for (size_t i = 0; i < table->max_entries; ++i) {
    if (table->entries[i] == NULL) {
      printf("[%zu]: --empty--\n", i);
    } else {
      ht_entry_t *entry = table->entries[i];
      printf("[%zu]: key: %s, value: %p\n", i, entry->key, entry->value);
    }
  }
}

/**
 * @brief Put (insert) a value into a hash table
 *
 * @param table table to put into
 * @param key key to put in
 * @param value value to put in
 */
void ht_put(ht_t *table, const char *key, const void *value) {
  // Table should at maximum be at 50% capacity
  if (table->n_entries + 1 > table->max_entries / 2) {
    ht_expand(table);
  }

  // Make new ht_entry
  ht_entry_t *new_entry = malloc(sizeof(ht_entry_t));
  if (new_entry == NULL) {
    err_malloc_fail();
  }
  new_entry->key = key;
  new_entry->value = value;

  // Insert entry into ht
  uint32_t hash_index = hash(key) % table->max_entries;
  ht_entry_t *existing_entry = table->entries[hash_index];

  // No entry at hash_index
  if (existing_entry == NULL) {
    table->entries[hash_index] = new_entry;
    ++table->n_entries;
    return;
  }

  // Same key has already been hashed (updating existing key)
  if (existing_entry->key == key) {
    existing_entry->value = value;
    return;
  }

  // Go to next index until there is an available spot
  while (table->entries[++hash_index] != NULL)
    ;

  table->entries[hash_index] = new_entry;
  ++table->n_entries;
}
