#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable.h"
#include "nonstdlib/nstring.h"

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
  size_t old_rehashed_index = old->hash % table->capacity;

  // Move from old index to first available index at or after the new index
  table->entries[old_hash_index] = NULL;
  while (table->entries[old_rehashed_index] != NULL) {
    ++old_rehashed_index;

    // Wrap to 0 on overflow
    if (old_rehashed_index >= table->capacity)
      old_rehashed_index = 0;
  }

  table->entries[old_rehashed_index] = old;
}

/**
 * @brief djb2 hash function.
 *
 * @return the key hashed. (needs to be %'d by table size to get index into
 * a hashtable)
 */
uint32_t ht_hash(const string_t *key) {
  uint32_t hash = 5381;

  for (size_t i = 0; i < key->len; ++i)
    hash = hash * 33 + key->s[i];

  return hash;
}

/**
 * @brief Get an element from a hash table.
 *
 * @param table table to get from
 * @param key key to get
 * @param len string length of the key
 * @return value of the given key
 */
void *ht_get(const ht_t *table, const string_t *key) {
  size_t index = ht_hash(key) % table->capacity;
  ht_entry_t *entry = table->entries[index];

  while (entry != NULL) {
    if (string_compare(entry->key, key) == 0)
      return entry->value;

    // Wrap to 0 on overflow
    if (index >= table->capacity - 1)
      index = 0;
    else
      ++index;

    entry = table->entries[index];
  }

  return NULL;
}

/**
 * @brief Initialize an empty hash table. Returned value needs to be freed by
 * ht_free.
 *
 * @param init_size the initial size of the hash table, can be changed by ht_put
 * @return a malloc'd hash table
 */
ht_t *ht_init(size_t init_capacity) {
  ht_t *table = malloc(sizeof(*table));
  if (table == NULL)
    err_malloc_fail();

  table->size = 0;
  table->capacity = init_capacity;
  table->entries = calloc(init_capacity, sizeof(table->entries));
  if (table->entries == NULL)
    err_malloc_fail();

  return table;
}

/**
 * @brief Doubles the size of a hash table.
 *
 * @param table hash table to expand the size of
 */
void ht_expand(ht_t *table) {
  size_t prev_capacity = table->capacity;
  table->capacity *= 2;
  table->entries =
      realloc(table->entries, table->capacity * sizeof(table->entries));
  if (table->entries == NULL)
    err_malloc_fail();

  // Set new indexes to NULL
  for (size_t i = prev_capacity; i < table->capacity; ++i)
    table->entries[i] = NULL;

  // Loop through table and reindex based on new size
  for (size_t i = 0; i < prev_capacity; ++i)
    if (table->entries[i] != NULL)
      ht_rehash_index(table, i);
}

/**
 * @brief Frees memory allocated for hash table.
 *
 * @param table table to free memory for
 */
void ht_free(ht_t *table) {
  for (size_t i = 0; i < table->capacity; ++i)
    if (table->entries[i] != NULL)
      free(table->entries[i]);

  free(table->entries);
  free(table);
}

/**
 * @brief Print contents of hash table
 *
 * @param table table to print
 */
void ht_print(const ht_t *table) {
  for (size_t i = 0; i < table->capacity; ++i) {
    if (table->entries[i] == NULL) {
      printf("[%zu]: --empty--\n", i);
    } else {
      ht_entry_t *entry = table->entries[i];
      printf("[%zu]: key: %.*s, value: %p\n", i, (int)entry->key->len,
             entry->key->s, entry->value);
    }
  }
}

static ht_entry_t *ht_create_entry(string_t *key, void *value, size_t hash) {
  ht_entry_t *entry = malloc(sizeof(*entry));
  entry->key = key;
  entry->value = value;
  entry->hash = hash;

  return entry;
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
void ht_put(ht_t *table, string_t *key, void *value) {
  // Table should at maximum be at 50% capacity to avoid collisions
  if (table->size + 1 > table->capacity / 2)
    ht_expand(table);

  uint32_t hash = ht_hash(key);
  size_t hash_index = hash % table->capacity;
  const ht_entry_t *existing_entry = table->entries[hash_index];

  if (existing_entry == NULL) {
    // New key, no collision
    table->entries[hash_index] = ht_create_entry(key, value, hash);
    ++table->size;

  } else if (string_compare(existing_entry->key, key) != 0) {
    // New key, but hash_index is occupied (collision)
    while (table->entries[hash_index] != NULL) {
      ++hash_index;

      // Wrap around to 0 for overflows
      if (hash_index >= table->capacity)
        hash_index = 0;
    }

    table->entries[hash_index] = ht_create_entry(key, value, hash);
    ++table->size;

  } else {
    // Existing key, update its value
    table->entries[hash_index]->value = value;
  }
}
