#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "hashtable.h"

/**
 * @brief djb2 hash function.
 *
 * @return the key hashed. (needs to be %'d by table size to get index into
 * hashtable)
 */
static uint32_t hash(const char *key, size_t key_size) {
  uint32_t hash = 5381;

  for (size_t i = 0; i < key_size; ++i) {
    hash = hash * 33 + key[i];
  }

  return hash;
}

/**
 * @brief Rehashes entry at old_hash_index and inserts it into the new hash
 * index. Used if the tables max entries has changed and the old hash index may
 * no longer be correct for the given entry.
 *
 * @param table table to update entry in
 * @param old_hash_index the old hash index of the entry we want to update
 */
static void ht_rehash_index(ht_t *table, size_t old_hash_index) {
  ht_entry_t *entry = table->entries[old_hash_index];
  uint32_t new_hash_index =
      hash(entry->key, strlen(entry->key)) % table->max_entries;
  if (new_hash_index == old_hash_index) {
    return;
  }

  // Move from old index to first available index at or after the new index
  table->entries[old_hash_index] = NULL;
  while (table->entries[new_hash_index] != NULL) {
    ++new_hash_index;

    if (new_hash_index >= table->max_entries) {
      new_hash_index = 0;
    }
  }

  table->entries[new_hash_index] = entry;
}

/**
 * @brief Constructor for new hashtable entries. Returned value needs to be
 * freed.
 *
 * @param key key to hashtable entry
 * @param value value associated with the key
 * @return constructed ht_entry_t
 */
static ht_entry_t *ht_create_entry(const char *key, const void *value,
                                   size_t value_size) {
  ht_entry_t *entry = malloc(sizeof(*entry));
  if (entry == NULL) {
    err_malloc_fail();
  }

  size_t key_len = strlen(key) + 1;

  entry->key = malloc(key_len);
  if (entry->key == NULL) {
    err_malloc_fail();
  }
  entry->value = malloc(value_size);
  if (entry->value == NULL) {
    // TODO: ht_free()
    free((void *)entry->key);
    err_malloc_fail();
  }

  memcpy((void *)entry->key, key, key_len);
  memcpy(entry->value, value, value_size);

  return entry;
}

/**
 * @brief Get an element from a hash table.
 *
 * @param table table to get from
 * @param key key to get
 * @return value of the given key
 */
void *ht_get(const ht_t *table, const char *key) {
  uint32_t index = hash(key, strlen(key)) % table->max_entries;
  ht_entry_t *entry = table->entries[index];
  if (entry == NULL) {
    return NULL;
  }

  while (strcmp(entry->key, key) != 0) {
    entry = table->entries[index++];
    if (entry == NULL) {
      return NULL;
    }
  }

  return entry->value;
}

/**
 * @brief Initialize an empty hash table. Returned value needs to be freed by
 * ht_free.
 *
 * @param init_size the initial size of the hash table, can be changed by ht_put
 * @return a malloc'd hash table
 */
ht_t *ht_init(uint32_t init_max_entries) {
  ht_t *new_ht = malloc(sizeof(*new_ht));
  if (new_ht == NULL) {
    return NULL;
  }

  new_ht->n_entries = 0;
  new_ht->max_entries = init_max_entries;
  new_ht->entries = malloc(init_max_entries * sizeof(new_ht->entries));
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
 * @brief Doubles the size of a hash table.
 *
 * @param table hash table to expand the size of
 */
void ht_expand(ht_t *table) {
  uint32_t prev_max_entries = table->max_entries;
  table->max_entries *= 2;
  table->entries =
      realloc(table->entries, table->max_entries * sizeof(ht_entry_t *));
  for (size_t i = prev_max_entries; i < table->max_entries; ++i) {
    table->entries[i] = NULL;
  }

  // Loop through table and reindex based on new size
  for (size_t i = 0; i < prev_max_entries; ++i) {
    if (table->entries[i] == NULL) {
      continue;
    }

    ht_rehash_index(table, i);
  }
}

/**
 * @brief Frees memory allocated for hash table.
 *
 * @param table table to free memory for
 */
void ht_free(const ht_t *table) {
  for (size_t i = 0; i < table->max_entries; ++i) {
    if (table->entries[i] != NULL) {
      free((void *)table->entries[i]->key);
      free(table->entries[i]->value);
      free(table->entries[i]);
    }
  }

  free(table->entries);
  free((void *)table);
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
void ht_put(ht_t *table, const char *key, void *value, size_t value_size) {
  // Table should at maximum be at 50% capacity
  if (table->n_entries + 1 > table->max_entries / 2) {
    ht_expand(table);
  }

  uint32_t hash_index = hash(key, strlen(key)) % table->max_entries;
  const ht_entry_t *existing_entry = table->entries[hash_index];

  if (existing_entry == NULL) {
    // New key
    table->entries[hash_index] = ht_create_entry(key, value, value_size);
    ++table->n_entries;

  } else if (strcmp(existing_entry->key, key) != 0) {
    // New key, but hash_index is occupied
    while (table->entries[hash_index] != NULL) {
      ++hash_index;

      if (hash_index >= table->max_entries) {
        hash_index = 0;
      }
    }

    table->entries[hash_index] = ht_create_entry(key, value, value_size);
    ++table->n_entries;
  } else {
    // Existing key, update its value
    table->entries[hash_index]->value =
        realloc(table->entries[hash_index]->value, value_size);
    memcpy(table->entries[hash_index]->value, value, value_size);
  }
}
