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
static uint32_t hash(const char *key) {
  uint32_t hash = 5381;

  for (size_t i = 0; i < strlen(key); ++i) {
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
static void ht_update_entry(ht_t *table, size_t old_hash_index) {
  ht_entry_t *entry = table->entries[old_hash_index];
  uint32_t new_hash_index = hash(entry->key) % table->max_entries;
  if (new_hash_index == old_hash_index) {
    return;
  }

  table->entries[old_hash_index] = NULL;
  while (table->entries[++new_hash_index] != NULL)
    ;

  table->entries[new_hash_index] = entry;
}

/**
 * @brief Get an element from a hash table.
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

  while (strcmp(entry->key, key) != 0) {
    entry = table->entries[index++];
    if (entry == NULL) {
      return NULL;
    }
  }

  return entry->value;
}

/**
 * @brief Constructor for new hashtable entries. Returned value needs to be
 * freed.
 *
 * @param key key to hashtable entry
 * @param value value associated with the key
 * @return constructed ht_entry_t
 */
static ht_entry_t *ht_create_entry(const char *key, const char *value) {
  ht_entry_t *entry = malloc(sizeof(ht_entry_t));
  if (entry == NULL) {
    err_malloc_fail();
  }
  entry->key = key;
  entry->value = value;

  return entry;
}

/**
 * @brief Initialize an empty hash table. Returned value needs to be freed by
 * ht_free.
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
  new_ht->entries = malloc(init_max_entries * sizeof(ht_entry_t *));
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
 * @brief Doubles the size of a hash table
 *
 * @param table hash table to expand the size of
 */
void ht_expand(ht_t *table) {
  uint32_t prev_max_entries = table->max_entries;
  table->max_entries *= 2;
  table->entries =
      realloc(table->entries, sizeof(ht_entry_t) * table->max_entries);

  // Loop through table and reindex based on new size
  for (size_t i = 0; i < prev_max_entries; ++i) {
    if (table->entries[i] == NULL) {
      continue;
    }
    ht_update_entry(table, i);
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

// void ht_put(ht_t *table, const char *key, const void *value) {
//   // Ensure table capacity is sufficient
//   if (table->n_entries + 1 > table->max_entries / 2) {
//     ht_expand(table);
//   }
//
//   uint32_t hash_index = hash(key) % table->max_entries;
//
//   // Search for an existing entry with the same key or the first empty slot
//   while (table->entries[hash_index] != NULL &&
//          strcmp(table->entries[hash_index]->key, key) != 0) {
//     hash_index = (hash_index + 1) %
//                  table->max_entries; // Use linear probing with wrapping
//   }
//
//   // At this point, hash_index is either an empty slot or an entry with the
//   same
//   // key
//   if (table->entries[hash_index] == NULL) {
//     // If it's an empty slot, create a new entry
//     ht_entry_t *new_entry = malloc(sizeof(ht_entry_t));
//     if (new_entry == NULL) {
//       err_malloc_fail(); // Ensure this function appropriately handles the
//                          // error, e.g., exit or return
//     }
//     new_entry->key = key;     // Assign the key
//     new_entry->value = value; // Assign the value
//
//     table->entries[hash_index] = new_entry; // Insert the new entry
//     ++table->n_entries;
//   } else {
//     // If an entry with the same key was found, update the value directly
//     // Depending on your memory management strategy, you might need to
//     // free/replace the value
//     table->entries[hash_index]->value = value;
//   }
// }

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

  // Insert entry into ht
  uint32_t hash_index = hash(key) % table->max_entries;
  ht_entry_t *existing_entry = table->entries[hash_index];

  // No entry at hash_index
  if (existing_entry == NULL) {
    table->entries[hash_index] = ht_create_entry(key, value);
    ++table->n_entries;
    return;
  }

  // Same key has already been hashed (updating existing key)
  if (strcmp(existing_entry->key, key) == 0) {
    // TODO: malloc/memcpy value?
    table->entries[hash_index]->value = value;
    return;
  }

  // Go to next index until there is an available spot
  while (table->entries[++hash_index] != NULL)
    ;

  table->entries[hash_index] = ht_create_entry(key, value);
  ++table->n_entries;
}
