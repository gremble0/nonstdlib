#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable.h"

// TODO: expose as public
/**
 * @brief djb2 hash function.
 *
 * @return the key hashed. (needs to be %'d by table size to get index into
 * hashtable)
 */
static uint32_t hash(const char *key, size_t key_size) {
  uint32_t hash = 5381;

  for (size_t i = 0; i < key_size; ++i)
    hash = hash * 33 + key[i];

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
  ht_entry_t *old = table->entries[old_hash_index];
  uint32_t old_rehashed =
      hash(old->key, strlen(old->key) + 1) % table->max_entries;
  if (old_rehashed == old_hash_index)
    return;

  // Move from old index to first available index at or after the new index
  table->entries[old_hash_index] = NULL;
  while (table->entries[old_rehashed] != NULL) {
    ++old_rehashed;

    if (old_rehashed >= table->max_entries)
      old_rehashed = 0;
  }

  table->entries[old_rehashed] = old;
}

/**
 * @brief Get an element from a hash table.
 *
 * @param table table to get from
 * @param key key to get
 * @param key_size string length of the key (including nullbyte)
 * @return value of the given key
 */
void *ht_get(const ht_t *table, const char *key, size_t key_size) {
  uint32_t index = hash(key, key_size) % table->max_entries;
  ht_entry_t *entry = table->entries[index];
  if (entry == NULL)
    return NULL;

  while (strcmp(entry->key, key) != 0) {
    entry = table->entries[index++];
    if (entry == NULL)
      return NULL;
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
ht_t *ht_init(size_t init_max_entries) {
  ht_t *table = malloc(sizeof(*table));
  if (table == NULL)
    err_malloc_fail();

  table->n_entries = 0;
  table->max_entries = init_max_entries;
  table->entries =
      malloc(init_max_entries * sizeof(table->entries)); // TODO: calloc
  if (table->entries == NULL)
    err_malloc_fail();

  for (size_t i = 0; i < init_max_entries; ++i)
    table->entries[i] = NULL;

  return table;
}

/**
 * @brief Doubles the size of a hash table.
 *
 * @param table hash table to expand the size of
 */
void ht_expand(ht_t *table) {
  size_t prev_max_entries = table->max_entries;
  table->max_entries *= 2;
  table->entries =
      realloc(table->entries, table->max_entries * sizeof(table->entries));
  if (table->entries == NULL)
    err_malloc_fail();

  // Set new indexes to NULL
  for (size_t i = prev_max_entries; i < table->max_entries; ++i)
    table->entries[i] = NULL;

  // Loop through table and reindex based on new size
  for (size_t i = 0; i < prev_max_entries; ++i)
    if (table->entries[i] != NULL)
      ht_rehash_index(table, i);
}

/**
 * @brief Frees memory allocated for hash table.
 *
 * @param table table to free memory for
 */
void ht_free(ht_t *table) {
  for (size_t i = 0; i < table->max_entries; ++i) {
    if (table->entries[i] != NULL)
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
void ht_print(const ht_t *table) {
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
 * @param key_size string length of the key (including nullbyte)
 * @param value value to put in
 * @param value_size size of value to put in
 */
void ht_put(ht_t *table, char *key, size_t key_size, void *value) {
  // Table should at maximum be at 50% capacity
  if (table->n_entries + 1 > table->max_entries / 2)
    ht_expand(table);

  uint32_t hash_index = hash(key, key_size) % table->max_entries;
  const ht_entry_t *existing_entry = table->entries[hash_index];

  if (existing_entry == NULL) {
    // New key
    table->entries[hash_index] = malloc(sizeof(*table->entries[hash_index]));
    table->entries[hash_index]->key = key;
    table->entries[hash_index]->value = value;
    // ht_create_entry(key, key_size, value, value_size);
    ++table->n_entries;

  } else if (strncmp(existing_entry->key, key, key_size) != 0) {
    // New key, but hash_index is occupied (collision)
    while (table->entries[hash_index] != NULL) {
      ++hash_index;

      // Wrap around to 0 for overflows
      if (hash_index >= table->max_entries)
        hash_index = 0;
    }

    table->entries[hash_index] = malloc(sizeof(*table->entries[hash_index]));
    table->entries[hash_index]->key = key;
    table->entries[hash_index]->value = value;
    ++table->n_entries;
  } else {
    // Existing key, update its value
    table->entries[hash_index]->value = value;
  }
}
